#ifndef GENERATOR_H_
#define GENERATOR_H_
#include "Element.h"
#include <vector>

class Generator
{
public:

	// 根据所有Solid向vertices加入结点信息 
	void generateBody(std::vector<Solid*> solids, std::vector<glm::vec3>& vertices);
	
	// 根据solid向vertices中加入结点信息
	void generateSolid(Solid* solid, std::vector<glm::vec3>& vertices);

	// 根据face向vertices中加入结点信息
	// 注意face中有innerLoop时需要以不同的方式三角化
	void generateFace(Face* face, std::vector<glm::vec3>& vertices);

	void generateRectangle(Loop* loop, std::vector<glm::vec3>& vertices);

	void generateRing(Loop* outterloop, Loop* innerLoop, std::vector<glm::vec3>& vertices);

	void swap(Point& p1, Point& p2);

};



#endif