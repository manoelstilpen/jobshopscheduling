#ifndef CONSTRUCTIVE_GREEDY_HPP
#define CONSTRUCTIVE_GREEDY_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "../Evaluator.hpp"
#include "Constructive.hpp"

#include <iostream>
#include <algorithm>  // sort
#include <math.h>	  // ceil

using namespace twtjssp;

class ConstructiveGreedy : public Constructive{

public:

	ConstructiveGreedy();
	ConstructiveGreedy(ProblemInstance p, double alpha = 0.5);

	virtual Solution apply();
	virtual void print_graph();

private:

	double alpha;

};

#endif