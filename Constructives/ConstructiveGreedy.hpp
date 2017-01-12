#ifndef CONSTRUCTIVE_GREEDY_HPP
#define CONSTRUCTIVE_GREEDY_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"

#include <iostream>
#include <algorithm>  // sort
#include <math.h>	  // ceil

using namespace twtjssp;

class ConstructiveGreedy{

public:

	ConstructiveGreedy();
	ConstructiveGreedy(double alpha);

	Solution generate_solution();
	Solution aloca_tarefa(Solution, Schedule);

	void set_instance(ProblemInstance);

private:
	ProblemInstance instance;
	ScheduleMatrix jobs;
	double alpha;
};

#endif