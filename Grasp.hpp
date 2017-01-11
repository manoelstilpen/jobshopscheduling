#ifndef GRASP
#define GRASP

#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "Evaluator.hpp"

using namespace twtjssp;

class Grasp{

public:
	Grasp();
	Grasp(ProblemInstance instance, double alpha);

	Solution apply_grasp();
	Solution alocaTarefa(Solution* solution, Schedule tarefa);

	void set_alpha(double);
	void set_instance(ProblemInstance);
	void set_repeat(int);

private:
	ProblemInstance instance;
	ScheduleMatrix jobs;
	double alpha;
	int repeat;
};

#endif