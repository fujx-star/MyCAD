#include "EulerOperation.h"

#include <iostream>

// �½��塢��ͻ�������point��vertex�½���
Solid* mvfs(Point point, Vertex*& vertex)
{
	Solid* solid = new Solid();
	Face* face = new Face();
	Loop* loop = new Loop();

	vertex = new Vertex();
	vertex->m_point = new Point();
	vertex->m_point->setPoint(point);

	solid->m_sFaces = face;
	face->m_fSolid = solid;
	face->m_fLoops = loop;
	loop->m_lFace = face;

	return solid;
}

// ����point�����µ㣬ͬʱ�����µ���ָ����v1���γ�һ���ߣ�������v1Ϊ���İ��
HalfEdge* mev(Vertex* v1, Point point, Loop*& loop)
{
	//std::cout << *v1 << std::endl << point;
	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();
	Edge* edge = new Edge();
	Vertex* v2 = new Vertex();

	v2->m_point = new Point();
	v2->m_point->setPoint(point);

	// ����edge,he1,he2֮���ϵ
	edge->m_firstHe = he1;
	edge->m_secondHe = he2;
	he1->m_edge = he2->m_edge = edge;

	he1->m_heLoop = he2->m_heLoop = loop;
	he1->m_startV = he2->m_endV = v1;
	he1->m_endV = he2->m_startV = v2;
	he1->m_adjacentHe = he2;
	he2->m_adjacentHe = he1;

	// ���loop��ԭ��û�бߣ������loop�м���ߣ���he1,he2�ɻ�
	if (loop->m_lHalfEdge == nullptr)
	{
		loop->m_lHalfEdge = he1;
		he1->m_nextHe = he1->m_prevHe = he2;
		he2->m_nextHe = he2->m_prevHe = he1;
	}

	// ���loop���Ѿ��бߣ����±߼���loop
	else
	{
		HalfEdge* he = loop->m_lHalfEdge;

		while (he->m_endV != v1)
		{
			he = he->m_nextHe;
		}

		he2->m_nextHe = he->m_nextHe;
		he->m_nextHe->m_prevHe = he2;
		he->m_nextHe = he1;
		he1->m_prevHe = he;
		he1->m_nextHe = he2;
		he2->m_prevHe = he1;
	}

	// ά���߱�
	Solid* solid = loop->m_lFace->m_fSolid;
	Edge* curEdge = solid->m_sEdges;

	if (curEdge == nullptr)
	{
		solid->m_sEdges = edge;
		return he1;
	}

	while (curEdge->m_nextE != nullptr)
	{
		curEdge = curEdge->m_nextE;
	}

	curEdge->m_nextE = edge;
	edge->m_prevE = curEdge;

	return he1;
}

// ��oldLoop�в����ڵ�v1��v2�����������γ��µ������solid�У�����newLoop
Loop* mef(Vertex* v1, Vertex* v2, Loop*& oldLoop)
{

	HalfEdge* he1 = new HalfEdge();
	HalfEdge* he2 = new HalfEdge();
	Edge* edge = new Edge();

	// ����edge,he1,he2֮���ϵ
	edge->m_firstHe = he1;
	edge->m_secondHe = he2;
	he1->m_edge = he2->m_edge = edge;

	he1->m_startV = he2->m_endV = v1;
	he1->m_endV = he2->m_startV = v2;
	he1->m_adjacentHe = he2;
	he2->m_adjacentHe = he1;

	// �ֱ��ҵ���v1,v2Ϊ���İ��
	HalfEdge* tmpHe = oldLoop->m_lHalfEdge;
	HalfEdge* tmpHe1;
	HalfEdge* tmpHe2;

	while (tmpHe->m_startV != v1)
	{
		tmpHe = tmpHe->m_nextHe;
	}
	tmpHe1 = tmpHe;

	while (tmpHe->m_startV != v2)
	{
		tmpHe = tmpHe->m_nextHe;
	}
	tmpHe2 = tmpHe;

	// ע��v1��v2�ڻ��е����λ�ã�������ڻ��Ķ˵㣬��Ҫ�ҵ���ȷ�İ��
	tmpHe = tmpHe->m_nextHe;
	while (tmpHe->m_startV != v2)
	{
		tmpHe = tmpHe->m_nextHe;
	}
	if (tmpHe != tmpHe2)
	{
		tmpHe2 = tmpHe;
	}

	// ���µı߼���oldLoop��,�������loop
	// ע����δ����˳�򣡣���
	he1->m_nextHe = tmpHe2;
	he1->m_prevHe = tmpHe1->m_prevHe;
	tmpHe1->m_prevHe->m_nextHe = he1;
	he2->m_nextHe = tmpHe1;
	tmpHe1->m_prevHe = he2;
	he2->m_prevHe = tmpHe2->m_prevHe;
	tmpHe2->m_prevHe->m_nextHe = he2;
	tmpHe2->m_prevHe = he1;

	oldLoop->m_lHalfEdge = he1;
	Loop* newLoop = new Loop();
	newLoop->m_lHalfEdge = he2;

	// ��newLoop�����½�����newFace�У���newFace����ԭ����solid��
	Solid* solid = oldLoop->m_lFace->m_fSolid;
	Face* newFace = new Face();
	newFace->m_fSolid = solid;
	newFace->m_fLoops = newLoop;
	newLoop->m_lFace = newFace;
	
	Face* tmpFace = solid->m_sFaces;
	while (tmpFace->m_nextF != nullptr)
	{
		tmpFace = tmpFace->m_nextF;
	}
	tmpFace->m_nextF = newFace;
	newFace->m_prevF = tmpFace;

	// ά��solid��edge�б�
	Edge* curEdge = solid->m_sEdges;

	if (curEdge == nullptr)
	{
		solid->m_sEdges = edge;
	}
	else
	{
		while (curEdge->m_nextE != nullptr)
		{
			curEdge = curEdge->m_nextE;
		}
		curEdge->m_nextE = edge;
		edge->m_prevE = curEdge;
	}

	return newLoop;

}

// ��loop1��ȥ��v1��v2���ɵıߣ��Ͽ����γɵ�loop2Ҳ��������
Loop* kemr(Vertex* v1, Vertex* v2, Loop*& oldLoop)
{
	Solid* solid = oldLoop->m_lFace->m_fSolid;
	Face* face = oldLoop->m_lFace;
	Loop* newLoop = new Loop();

	HalfEdge* he = oldLoop->m_lHalfEdge;
	while (he->m_startV != v1 || he->m_endV != v2)
	{
		he = he->m_nextHe;
	}

	// ��ʱheΪ��v1Ϊ��㣬v2Ϊ�յ�İ��
	Edge* edge = he->m_edge;
	// ȥ���ñߺ�������ߵ����ӹ�ϵ��ı�
	he->m_prevHe->m_nextHe = he->m_adjacentHe->m_nextHe;
	he->m_adjacentHe->m_nextHe->m_prevHe = he->m_prevHe;
	he->m_adjacentHe->m_prevHe->m_nextHe = he->m_nextHe;
	he->m_nextHe->m_prevHe = he->m_adjacentHe->m_prevHe;

	// �µĻ�
	oldLoop->m_lHalfEdge = he->m_prevHe;
	newLoop->m_lHalfEdge = he->m_nextHe;

	// ���µĻ�������
	newLoop->m_lFace = face;
	if (face->m_fLoops == nullptr)
	{
		face->m_fLoops = newLoop;
	}
	else
	{
		Loop* tmpLoop = face->m_fLoops;
		while (tmpLoop->m_nextL != nullptr)
		{
			tmpLoop = tmpLoop->m_nextL;
		}
		tmpLoop->m_nextL = newLoop;
		newLoop->m_prevL = tmpLoop;
	}

	// ɾ����edge,ά���߱�
	Edge* tmpEdge = solid->m_sEdges;
	while (tmpEdge != edge)
	{
		tmpEdge = tmpEdge->m_nextE;
	}
	if (tmpEdge->m_prevE == nullptr)
	{
		solid->m_sEdges = tmpEdge->m_nextE;
	}
	else if (tmpEdge->m_nextE == nullptr)
	{
		tmpEdge->m_prevE->m_nextE = nullptr;
	}
	else
	{
		tmpEdge->m_prevE->m_nextE = tmpEdge->m_nextE;
		tmpEdge->m_nextE->m_prevE = tmpEdge->m_prevE;
	}

	return newLoop;
}

// ɾ��innerLoop���ڵ��棬��loop���뵽outterloop���ڵ���
void kfmrh(Loop* outterLoop, Loop*& innerLoop)
{
	Face* face1 = outterLoop->m_lFace;
	Face* face2 = innerLoop->m_lFace;
	innerLoop->m_lFace = face1;

	// ��loop�����Ӧ��
	if (face1->m_fLoops == nullptr)
	{
		face1->m_fLoops = innerLoop;
	}
	else
	{
		Loop* tmpLoop = face1->m_fLoops;
		while (tmpLoop->m_nextL != nullptr)
		{
			tmpLoop = tmpLoop->m_nextL;
		}
		tmpLoop->m_nextL = innerLoop;
		innerLoop->m_prevL = tmpLoop;
	}

	// ��solid���ҵ�face2��ɾ��
	Solid* solid = face1->m_fSolid;
	Face* tmpFace = solid->m_sFaces;
	while (tmpFace != face2)
	{
		tmpFace = tmpFace->m_nextF;
	}

	if (tmpFace->m_prevF == nullptr)
	{
		solid->m_sFaces = tmpFace->m_nextF;
	}
	else if (tmpFace->m_nextF == nullptr)
	{
		tmpFace->m_prevF->m_nextF = nullptr;
	}
	else
	{
		tmpFace->m_prevF->m_nextF = tmpFace->m_nextF;
		tmpFace->m_nextF->m_prevF = tmpFace->m_prevF;
	}

}

// ������face����direction����ɨ�ӵõ��µ��棬������solid��
Solid* sweep(Face* face, glm::vec3 direction, float d)
{
	Solid* solid = face->m_fSolid;
	HalfEdge* tmpHe;
	HalfEdge* he;
	Vertex* downVertex;
	Vertex* upVertex;
	Vertex* prevUpVertex;
	Vertex* startUpVertex;
	Vertex* startDownVertex;
	Point upPoint;

	for (Loop* loop = face->m_fLoops; loop != nullptr; loop = loop->m_nextL)
	{

		tmpHe = loop->m_lHalfEdge;
		startDownVertex = downVertex = tmpHe->m_startV;
		upPoint.setPoint(downVertex->m_point->p.x + direction.x * d, downVertex->m_point->p.y + direction.y * d, downVertex->m_point->p.z + direction.z * d);
		he = mev(downVertex, upPoint, loop);
		upVertex = he->m_endV;

		startUpVertex = upVertex;
		prevUpVertex = upVertex;
		tmpHe = tmpHe->m_nextHe;

		// ����loop�е����бߣ������ߺͶ�Ӧ����
		while (tmpHe->m_startV != startDownVertex)
		{
			downVertex = tmpHe->m_startV;
			upPoint.setPoint(downVertex->m_point->p.x + direction.x * d, downVertex->m_point->p.y + direction.y * d, downVertex->m_point->p.z + direction.z * d);
			he = mev(downVertex, upPoint, loop);
			upVertex = he->m_endV;
			mef(prevUpVertex, upVertex, loop);

			prevUpVertex = upVertex;
			tmpHe = tmpHe->m_nextHe;
		}

		mef(prevUpVertex, startUpVertex, loop);

	}

	return solid;
}