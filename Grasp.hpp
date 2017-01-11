#ifndef GRASP
#define GRASP

#include "Commons.hpp"
#include "ProblemInstance.hpp"

using namespace twtjssp;

class Grasp{

public:
	Grasp();
	Grasp(ProblemInstance instance, double alpha);

	Solution apply_grasp();

	void set_alpha(double);
	void set_instance(ProblemInstance);
	void set_repeat(int);

private:
	ProblemInstance instance;
	double alpha;
	int repeat;
};

#endif