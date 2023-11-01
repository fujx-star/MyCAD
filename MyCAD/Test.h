#ifndef _TEST_H_
#define _TEST_H_

#include "EulerOperation.h"
#include "Generator.h"
using namespace std;

class Test
{
public:
	static Solid* createBody();

	static void testSweep();

	static void testRingGenerator(vector<glm::vec3>& vertices);

	static void testSweepGenerator(vector<glm::vec3>& vertices);

	static void testSweepRingGenerator(vector<glm::vec3>& vertices);

};

#endif
