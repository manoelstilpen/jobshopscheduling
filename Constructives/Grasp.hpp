#ifndef GRASP
#define GRASP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "../Evaluator.hpp"

#include <algorithm>  // sort

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

	int get_atraso();

	void print();
	void print_graph();

private:
	ProblemInstance instance;
	ScheduleMatrix jobs;
	Solution solution;
	Evaluator evaluator;

	double alpha;
	int repeat;
	int media_atraso;
};

#endif