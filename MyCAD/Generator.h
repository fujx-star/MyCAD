#ifndef GENERATOR_H_
#define GENERATOR_H_
#include "Element.h"
#include <vector>

class Generator
{
public:

	// ��������Solid��vertices��������Ϣ 
	void generateBody(std::vector<Solid*> solids, std::vector<glm::vec3>& vertices);
	
	// ����solid��vertices�м�������Ϣ
	void generateSolid(Solid* solid, std::vector<glm::vec3>& vertices);

	// ����face��vertices�м�������Ϣ
	// ע��face����innerLoopʱ��Ҫ�Բ�ͬ�ķ�ʽ���ǻ�
	void generateFace(Face* face, std::vector<glm::vec3>& vertices);

	void generateRectangle(Loop* loop, std::vector<glm::vec3>& vertices);

	void generateRing(Loop* outterloop, Loop* innerLoop, std::vector<glm::vec3>& vertices);

	void swap(Point& p1, Point& p2);

};



#endif