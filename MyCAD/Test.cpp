#include "Test.h"
#include <iostream>

// 按照Vertex1->mev(Vertex1, Point2)->mev(Vertex1, Point3)->mev(Vertex3, Point4)的方法构造，
// Loop的顺序为1->3->4->2
Solid* Test::createBody()
{
    Solid* newSolid;

    Vertex* topUpperLeft;
    newSolid = mvfs(Point(-1.0, 1.0, 2.0), topUpperLeft);
    Loop* topLoop = newSolid->m_sFaces->m_fLoops;

    /*HalfEdge* topUpperHalfEdge = mev(topUpperLeft, Point(1.0, 0.5, 2.0), topLoop);
    Vertex* topUpperRight = topUpperHalfEdge->m_endV;
    HalfEdge* topLeftHalfEdge = mev(topUpperLeft, Point(-1.0, 0.5, -2.0), topLoop);
    Vertex* topBottomLeft = topLeftHalfEdge->m_endV;*/
    HalfEdge* topUpperHalfEdge = mev(topUpperLeft, Point(-1.0, 1.0, -2.0), topLoop);
    Vertex* topUpperRight = topUpperHalfEdge->m_endV;
    HalfEdge* topLeftHalfEdge = mev(topUpperLeft, Point(1.0, 1.0, 2.0), topLoop);
    Vertex* topBottomLeft = topLeftHalfEdge->m_endV;
    
    HalfEdge* topRightHalfEdge = mev(topUpperRight, Point(1.0, 1.0, -2.0), topLoop);
    Vertex* topBottomRight = topRightHalfEdge->m_endV;

    Loop* downLoop = mef(topBottomLeft, topBottomRight, topLoop);


    HalfEdge* upperLeftHalfEdge = mev(topUpperLeft, Point(-1.0, -1.0, 2.0), downLoop);
    Vertex* downUpperLeft = upperLeftHalfEdge->m_endV;

    /*HalfEdge* upperRightHalfEdge = mev(topUpperRight, Point(1.0, -0.5, 2.0), downLoop);
    Vertex* downUpperRight = upperRightHalfEdge->m_endV;
    HalfEdge* bottomLeftHalfEdge = mev(topBottomLeft, Point(-1.0, -0.5, -2.0), downLoop);
    Vertex* downBottomLeft = bottomLeftHalfEdge->m_endV;*/
    HalfEdge* upperRightHalfEdge = mev(topUpperRight, Point(-1.0, -1.0, -2.0), downLoop);
    Vertex* downUpperRight = upperRightHalfEdge->m_endV;
    HalfEdge* bottomLeftHalfEdge = mev(topBottomLeft, Point(1.0, -1.0, 2.0), downLoop);
    Vertex* downBottomLeft = bottomLeftHalfEdge->m_endV;

    HalfEdge* bottomRightHalfEdge = mev(topBottomRight, Point(1.0, -1.0, -2.0), downLoop);
    Vertex* downBottomRight = bottomRightHalfEdge->m_endV;

    Loop* upperLoop = mef(downUpperLeft, downUpperRight, downLoop);
    Loop* rightLoop = mef(downUpperRight, downBottomRight, downLoop);
    Loop* bottomLoop = mef(downBottomRight, downBottomLeft, downLoop);
    Loop* leftLoop = mef(downBottomLeft, downUpperLeft, downLoop);

    HalfEdge* topBridge = mev(topUpperLeft, Point(-0.5, 1.0, 1.5), topLoop);
    Vertex* topInnerUpperLeft = topBridge->m_endV;

    HalfEdge* topInnerUpperHalfEdge = mev(topInnerUpperLeft, Point(0.5, 1.0, 1.5), topLoop);
    Vertex* topInnerUpperRight = topInnerUpperHalfEdge->m_endV;
    HalfEdge* topInnerRightHalfEdge = mev(topInnerUpperRight, Point(0.5, 1.0, -1.5), topLoop);
    Vertex* topInnerBottomRight = topInnerRightHalfEdge->m_endV;
    /*HalfEdge* topInnerUpperHalfEdge = mev(topInnerUpperLeft, Point(0.5, 0.5, -1.5), topLoop);
    Vertex* topInnerUpperRight = topInnerUpperHalfEdge->m_endV;
    HalfEdge* topInnerRightHalfEdge = mev(topInnerUpperRight, Point(0.5, 0.5, 1.5), topLoop);
    Vertex* topInnerBottomRight = topInnerRightHalfEdge->m_endV;*/

    HalfEdge* topInnerLeftHalfEdge = mev(topInnerUpperLeft, Point(-0.5, 1.0, -1.5), topLoop);
    Vertex* topInnerBottomLeft = topInnerLeftHalfEdge->m_endV;
    Loop* downInnerLoop = mef(topInnerBottomLeft, topInnerBottomRight, topLoop);

    Loop* topInnerLoop = kemr(topUpperLeft, topInnerUpperLeft, topLoop);

    HalfEdge* upperLeftInnerHalfEdge = mev(topInnerUpperLeft, Point(-0.5, -1.0, 1.5), downInnerLoop);
    Vertex* downInnerUpperLeft = upperLeftInnerHalfEdge->m_endV;

    HalfEdge* upperRightInnerHalfEdge = mev(topInnerUpperRight, Point(0.5, -1.0, 1.5), downInnerLoop);
    Vertex* downInnerUpperRight = upperRightInnerHalfEdge->m_endV;
    HalfEdge* bottomLeftInnerHalfEdge = mev(topInnerBottomLeft, Point(-0.5, -1.0, -1.5), downInnerLoop);
    Vertex* downInnerBottomLeft = bottomLeftInnerHalfEdge->m_endV;
    /*HalfEdge* upperRightInnerHalfEdge = mev(topInnerUpperRight, Point(0.5, -0.5, 1.5), downInnerLoop);
    Vertex* downInnerUpperRight = upperRightInnerHalfEdge->m_endV;
    HalfEdge* bottomLeftInnerHalfEdge = mev(topInnerBottomLeft, Point(-0.5, -0.5, -1.5), downInnerLoop);
    Vertex* downInnerBottomLeft = bottomLeftInnerHalfEdge->m_endV;*/

    HalfEdge* bottomRightInnerHalfEdge = mev(topInnerBottomRight, Point(0.5, -1.0, -1.5), downInnerLoop);
    Vertex* downInnerBottomRight = bottomRightInnerHalfEdge->m_endV;

    Loop* upperInnerLoop = mef(downInnerUpperLeft, downInnerUpperRight, downInnerLoop);
    Loop* rightInnerLoop = mef(downInnerUpperRight, downInnerBottomRight, downInnerLoop);
    Loop* bottomInnerLoop = mef(downInnerBottomRight, downInnerBottomLeft, downInnerLoop);
    Loop* leftInnerLoop = mef(downInnerBottomLeft, downInnerUpperLeft, downInnerLoop);

    kfmrh(downLoop, downInnerLoop);

    topInnerLoop->setInner(true);
    downInnerLoop->setInner(true);

    return newSolid;
}


// 测试对一个含有4条HalfEdge的简单Loop的Face的sweep操作，将结果Solid输出
void Test::testSweep()
{
    Point point1(0.5, 0.5, 1.0), point2(0.5, -0.5, 1.0), point3(-0.5, 0.5, 1.0), point4(-0.5, -0.5, 1.0);
    Vertex* vertex;
    Solid* solid = mvfs(point1, vertex);
    Loop* loop = solid->m_sFaces->m_fLoops;
    HalfEdge* he2 = mev(vertex, point2, loop);
    HalfEdge* he3 = mev(vertex, point3, loop);
    HalfEdge* he4 = mev(he3->m_endV, point4, loop);
    mef(he2->m_endV, he4->m_endV, loop);
    solid = sweep(solid->m_sFaces, glm::vec3(0.0, 0.0, 1.0), 1.0);
    
    // 测试输出
    solid->printSolid();
}

// 对用基础操作（除sweep外的其他操作）创建的Solid可视化（此Solid有能正确指示面的法向的Loop方向）
void Test::testRingGenerator(vector<glm::vec3>& vertices)
{
    Solid* solid = createBody();
    solid->printSolid();
    Generator* generator = new Generator();
    generator->generateSolid(solid, vertices);
}

// 测试对一个含有4条HalfEdge的简单Loop的Face的sweep操作，将结果Solid可视化
void Test::testSweepGenerator(vector<glm::vec3>& vertices)
{
    Point point1(0.5, 0.5, 1.0), point2(0.5, -0.5, 1.0), point3(-0.5, 0.5, 1.0), point4(-0.5, -0.5, 1.0);
    Vertex* vertex;
    Solid* solid = mvfs(point1, vertex);
    Loop* loop = solid->m_sFaces->m_fLoops;
    HalfEdge* he2 = mev(vertex, point2, loop);
    HalfEdge* he3 = mev(vertex, point3, loop);
    HalfEdge* he4 = mev(he3->m_endV, point4, loop);
    mef(he2->m_endV, he4->m_endV, loop);
    solid = sweep(solid->m_sFaces, glm::vec3(0.0, 0.0, 1.0), 1.0);

    // solid->printSolid();

    Generator* generator = new Generator();
    generator->generateSolid(solid, vertices);
}

void Test::testSweepRingGenerator(vector<glm::vec3>& vertices)
{
    // 原来的面经过扫掠后会消失，需要新建一个newFace加入newSolid中
    Face* newFace = createBody()->m_sFaces->m_nextF;
    newFace->m_nextF = nullptr;

    Solid* newSolid = createBody();
    newSolid->m_sFaces = newSolid->m_sFaces->m_nextF;
    newSolid->m_sFaces->m_nextF = nullptr;
    newSolid = sweep(newSolid->m_sFaces, glm::vec3(0.0, -1.0, 0.0), 1.0);

    Face* tmpFace = newSolid->m_sFaces;
    int cnt = 0;
    while (tmpFace->m_nextF != nullptr)
    {
        tmpFace = tmpFace->m_nextF;
    }
    tmpFace->m_nextF = newFace;

    newSolid->printSolid();

    Generator* generator = new Generator();
    generator->generateSolid(newSolid, vertices);
}

