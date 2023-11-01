#include "Element.h"

Solid::Solid() : m_prevS(nullptr), m_nextS(nullptr), m_sFaces(nullptr), m_sEdges(nullptr) {}

void Solid::printSolid()
{
	std::cout << "This solid has " << numOfFaces() << " faces:" << std::endl << std::endl;
	Face* tmpFace = m_sFaces;
	Loop* tmpLoop;
	while (tmpFace != nullptr)
	{
		std::cout << "This face has " << tmpFace->hasInnerLoop() << " inner loop" << std::endl;
		tmpLoop = tmpFace->m_fLoops;
		while (tmpLoop != nullptr)
		{
			std::cout << *tmpLoop << std::endl;
			tmpLoop = tmpLoop->m_nextL;
		}
		tmpFace = tmpFace->m_nextF;
		std::cout << std::endl;
	}

	std::cout << "------------The edges of this solid-----------" << std::endl;
	printEdges();
}

void Solid::printEdges()
{
	Edge* tmpEdge = m_sEdges;
	if (tmpEdge == nullptr)
	{
		std::cout << "This solid has no edge.";
	}
	else if (tmpEdge->m_nextE == nullptr)
	{
		std::cout << *tmpEdge;
	}
	else
	{
		while (tmpEdge->m_nextE != nullptr)
		{
			std::cout << *tmpEdge << ",";
			tmpEdge = tmpEdge->m_nextE;
		}
		std::cout << *tmpEdge;
	}
	
	std::cout << std::endl;

}

int Solid::numOfFaces()
{
	Face* tmpFace = m_sFaces;
	int cnt = 0;
	while (tmpFace != nullptr)
	{
		cnt++;
		tmpFace = tmpFace->m_nextF;
	}
	return cnt;
}

Face::Face() : m_fSolid(nullptr), m_prevF(nullptr), m_nextF(nullptr), m_fLoops(nullptr) {}

bool Face::hasInnerLoop()
{
	Loop* tmpLoop = m_fLoops;
	while (tmpLoop)
	{
		if (tmpLoop->m_isInner)
		{
			return true;
		}
		tmpLoop = tmpLoop->m_nextL;
	}
	return false;
}

int Face::numOfLoops()
{
	Loop* tmpLoop = m_fLoops;
	int cnt = 0;
	while (tmpLoop != nullptr)
	{
		cnt++;
		tmpLoop = tmpLoop->m_nextL;
	}
	return cnt;
}

Loop::Loop() : m_isInner(false), m_lFace(nullptr), m_prevL(nullptr), m_nextL(nullptr), m_lHalfEdge(nullptr) {}

void Loop::setInner(bool inner)
{
	m_isInner = inner;
}

HalfEdge::HalfEdge() : m_heLoop(nullptr), m_prevHe(nullptr), m_nextHe(nullptr), m_adjacentHe(nullptr), m_edge(nullptr), m_startV(nullptr), m_endV(nullptr) {}

Edge::Edge() : m_prevE(nullptr), m_nextE(nullptr), m_firstHe(nullptr), m_secondHe(nullptr) {}

Vertex::Vertex() : m_prevV(nullptr), m_nextV(nullptr), m_point(nullptr) {}

Point::Point() : p(0, 0, 0) {}

Point::Point(float x, float y, float z) : p(x, y, z) {}

void Point::setPoint(float x, float y, float z) 
{
	p.x = x;
	p.y = y;
	p.z = z;
}

void Point::setPoint(Point point)
{
	this->p.x = point.p.x;
	this->p.y = point.p.y;
	this->p.z = point.p.z;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
	out << "( " << point.p.x << ", " << point.p.y << ", " << point.p.z << " )";
	return out;
}

std::ostream& operator<<(std::ostream& out, const Vertex& vertex)
{
	out << *vertex.m_point;
	return out;
}

std::ostream& operator<<(std::ostream& out, const HalfEdge& he)
{
	out << *he.m_startV << "->" << *he.m_endV;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Edge& edge)
{
	out << *edge.m_firstHe->m_startV << "<->" << *edge.m_secondHe->m_startV;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Loop& loop)
{
	HalfEdge* tmpHe = loop.m_lHalfEdge;

	if (loop.m_isInner)
	{
		out << "This loop is an inner loop." << std::endl;
	}
	else
	{
		out << "This loop is an outter loop." << std::endl;
	}

	if (loop.m_lHalfEdge == nullptr)
	{
		out << "This loop has no half edge.";
	}
	else if (loop.m_lHalfEdge->m_nextHe == loop.m_lHalfEdge)
	{
		out << *(loop.m_lHalfEdge->m_startV) << "->" << *loop.m_lHalfEdge->m_endV << std::endl;
	}
	else
	{
		do
		{
			out << *tmpHe->m_startV << "->";
			tmpHe = tmpHe->m_nextHe;
		} while (tmpHe->m_nextHe != loop.m_lHalfEdge);
		out << *tmpHe->m_startV << "->" << *tmpHe->m_endV;
	}

	return out;
}