#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Solid;
class Face;
class Loop;
class HalfEdge;
class Edge;
class Vertex;
class Edge;
class Point;

class Solid
{
public:
	Solid();
	void printSolid();

	Solid* m_prevS;
	Solid* m_nextS;
	Face* m_sFaces;
	Edge* m_sEdges;

private:
	void printEdges();
	int numOfFaces();

};

class Face
{
public:
	Face();
	bool hasInnerLoop();
	int numOfLoops();

	Solid* m_fSolid;
	Face* m_prevF;
	Face* m_nextF;
	Loop* m_fLoops;
};

class Loop
{
public:
	Loop();
	friend std::ostream& operator<<(std::ostream& out, const Loop& loop);
	void setInner(bool inner);

	bool m_isInner;
	Face* m_lFace;
	Loop* m_prevL;
	Loop* m_nextL;
	HalfEdge* m_lHalfEdge;
};

class HalfEdge
{
public:
	HalfEdge();
	friend std::ostream& operator<<(std::ostream& out, const HalfEdge& he);

	Loop* m_heLoop;
	HalfEdge* m_prevHe;
	HalfEdge* m_nextHe;
	HalfEdge* m_adjacentHe;
	Edge* m_edge;
	Vertex* m_startV;
	Vertex* m_endV;
};

class Edge
{
public:
	Edge();
	friend std::ostream& operator<<(std::ostream& out, const Edge& edge);

	Edge* m_prevE;
	Edge* m_nextE;
	HalfEdge* m_firstHe;
	HalfEdge* m_secondHe;
};

class Vertex
{
public:
	Vertex();
	friend std::ostream& operator<<(std::ostream& out, const Vertex& vertex);

	Vertex* m_prevV;
	Vertex* m_nextV;
	Point* m_point;
};

class Point
{
public:
	Point();
	Point(float x, float y, float z);
	void setPoint(float x, float y, float z);
	void setPoint(Point point);
	friend std::ostream& operator<<(std::ostream& out, const Point& point);

	glm::vec3 p;
	glm::vec3 color;
};

#endif