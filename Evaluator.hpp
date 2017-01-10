#ifndef EVALUATOR
#define EVALUATOR

#include "Commons.hpp"
#include "ProblemInstance.hpp"

class Evaluator{
public:
	Evaluator();
	Evaluator(Solution s, ProblemInstance p);

	void evaluateSolution();

	void set_instance(ProblemInstance);
	void set_solution(Solution);

private:
	ProblemInstance instance;
	Solution solution;
};

#endif