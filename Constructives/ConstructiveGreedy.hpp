#ifndef CONSTRUCTIVE_GREEDY_HPP
#define CONSTRUCTIVE_GREEDY_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "../Evaluator.hpp"

#include <iostream>
#include <algorithm>  // sort
#include <math.h>	  // ceil

using namespace twtjssp;

class ConstructiveGreedy{

public:

	ConstructiveGreedy();
	ConstructiveGreedy(ProblemInstance p, double alpha);

	Solution generate_solution();
	Solution aloca_tarefa(Solution, Schedule);

	void set_instance(ProblemInstance);
	void set_repeat(int);

	int get_atraso();

	void print();
	void print_graph();

private:
	ProblemInstance instance;
	Solution machines;
	ScheduleMatrix jobs;
	Evaluator evaluator;

	double alpha;
	int repeat;
	int media_atraso;
};

#endif