#ifndef EULER_OPERATION_H_
#define EULER_OPERATION_H_

#include "Element.h"

// 新建体、面和环，根据point和vertex新建点
Solid* mvfs(Point point, Vertex*& vertex);

// 基于point建立新点，同时连接新点与指定点v1，形成一条边
HalfEdge* mev(Vertex* v1, Point point, Loop*& loop);

// 将loop中不相邻的v1和v2连接起来，形成新的面加入solid中
Loop* mef(Vertex* v1, Vertex* v2, Loop*& loop);

// 在loop1中去除v1和v2连成的边，断开后将形成的loop2也加入面中
Loop* kemr(Vertex* v1, Vertex* v2, Loop*& loop1);

// 删除loop所在的面，将loop加入到outterloop所在的面
void kfmrh(Loop* outterLoop, Loop*& loop);

// 根据面face按照direction方向扫掠得到新的面，加入体solid中
Solid* sweep(Face* face, glm::vec3 direction, float d);

#endif