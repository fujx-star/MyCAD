#ifndef EULER_OPERATION_H_
#define EULER_OPERATION_H_

#include "Element.h"

// �½��塢��ͻ�������point��vertex�½���
Solid* mvfs(Point point, Vertex*& vertex);

// ����point�����µ㣬ͬʱ�����µ���ָ����v1���γ�һ����
HalfEdge* mev(Vertex* v1, Point point, Loop*& loop);

// ��loop�в����ڵ�v1��v2�����������γ��µ������solid��
Loop* mef(Vertex* v1, Vertex* v2, Loop*& loop);

// ��loop1��ȥ��v1��v2���ɵıߣ��Ͽ����γɵ�loop2Ҳ��������
Loop* kemr(Vertex* v1, Vertex* v2, Loop*& loop1);

// ɾ��loop���ڵ��棬��loop���뵽outterloop���ڵ���
void kfmrh(Loop* outterLoop, Loop*& loop);

// ������face����direction����ɨ�ӵõ��µ��棬������solid��
Solid* sweep(Face* face, glm::vec3 direction, float d);

#endif