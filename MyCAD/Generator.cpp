#include "Generator.h"

void Generator::generateBody(std::vector<Solid*> solids, std::vector<glm::vec3>& vertices)
{
	for (auto solid : solids)
	{
		generateSolid(solid, vertices);
	}
}

void Generator::generateSolid(Solid* solid, std::vector<glm::vec3>& vertices)
{
	Face* tmpFace = solid->m_sFaces;
	while (tmpFace != nullptr)
	{
		generateFace(tmpFace, vertices);
		tmpFace = tmpFace->m_nextF;
	}
}

void Generator::generateFace(Face* face, std::vector<glm::vec3>& vertices)
{

	// 默认所有face均为矩形
	// 如果face没有innerLoop，则直接将矩形三角化
	if (!face->hasInnerLoop())
	{
		Loop* tmpLoop = face->m_fLoops;
		while (tmpLoop != nullptr)
		{
			generateRectangle(tmpLoop, vertices);
			tmpLoop = tmpLoop->m_nextL;
		}
	}
	// 如果面中有环，默认为一个外环中有一个内环
	else
	{
		Loop* outter = new Loop();
		Loop* inner = new Loop();
		Loop* tmpLoop = face->m_fLoops;
		while (tmpLoop)
		{
			if (tmpLoop->m_isInner)
			{
				inner = tmpLoop;
			}
			else
			{
				outter = tmpLoop;
			}
			tmpLoop = tmpLoop->m_nextL;
		}
		generateRing(outter, inner, vertices);
	}
}

// 矩形的三角划分
void Generator::generateRectangle(Loop* loop, std::vector<glm::vec3>& vertices)
{
	HalfEdge* tmpHe;
	HalfEdge* startHe;
	startHe = tmpHe = loop->m_lHalfEdge;
	std::vector<Point> points;

	do
	{
		points.push_back(*tmpHe->m_startV->m_point);
		tmpHe = tmpHe->m_nextHe;
	} while (startHe != tmpHe);

	glm::vec3 normal = glm::normalize(glm::cross(points[1].p - points[0].p, points[2].p - points[0].p));

	// 0,1,3为一个三角形，1,2,3为一个三角形
	vertices.push_back(points[0].p);
	vertices.push_back(normal);
	vertices.push_back(points[1].p);
	vertices.push_back(normal);
	vertices.push_back(points[3].p);
	vertices.push_back(normal);

	vertices.push_back(points[1].p);
	vertices.push_back(normal);
	vertices.push_back(points[2].p);
	vertices.push_back(normal);
	vertices.push_back(points[3].p);
	vertices.push_back(normal);
}

// 矩形环的三角划分（注意三角化API仅适用于内外为相同多边形）
void Generator::generateRing(Loop* outterloop, Loop* innerLoop, std::vector<glm::vec3>& vertices)
{
	
	HalfEdge* tmpHe;
	HalfEdge* startHe;
	std::vector<Point> outterPoints, innerPoints;
	startHe = tmpHe = outterloop->m_lHalfEdge;

	do
	{
		outterPoints.push_back(*tmpHe->m_startV->m_point);
		tmpHe = tmpHe->m_nextHe;
	} while (startHe != tmpHe);

	startHe = tmpHe = innerLoop->m_lHalfEdge;

	do
	{
		innerPoints.push_back(*tmpHe->m_startV->m_point);
		tmpHe = tmpHe->m_nextHe;
	} while (startHe != tmpHe);

	size_t size = outterPoints.size();		// 内外形状相同
	// 按照外环中点的顺序将内环中的最近点按照相同顺序排列，用于三角化
	float minDistance, tmpDistance;
	size_t innerIndex;
	for (size_t i = 0; i < size; i++)
	{
		minDistance = FLT_MAX;
		innerIndex = -1;
		for (size_t j = i; j < size; j++)
		{
			tmpDistance = glm::distance(outterPoints[i].p, innerPoints[j].p);
			if (tmpDistance < minDistance)
			{
				minDistance = tmpDistance;
				innerIndex = j;
			}
		}
		swap(innerPoints[i], innerPoints[innerIndex]);
	}

	glm::vec3 normal = glm::normalize(glm::cross(outterPoints[1].p - outterPoints[0].p, outterPoints[2].p - outterPoints[0].p));

	// 预处理完成，开始三角划分
	for (size_t i = 0; i < size; i++)
	{
		vertices.push_back(outterPoints[i].p);
		vertices.push_back(normal);
		vertices.push_back(innerPoints[i].p);
		vertices.push_back(normal);
		vertices.push_back(innerPoints[(i + 1) % size].p);
		vertices.push_back(normal);

		vertices.push_back(outterPoints[i].p);
		vertices.push_back(normal);
		vertices.push_back(outterPoints[(i + 1) % size].p);
		vertices.push_back(normal);
		vertices.push_back(innerPoints[(i + 1) % size].p);
		vertices.push_back(normal);
	}
}

void Generator::swap(Point& p1, Point& p2)
{
	Point tmpP = p1;
	p1 = p2;
	p2 = tmpP;
}
