#ifndef EVALUATOR
#define EVALUATOR

#include "Commons.hpp"
#include "Solution.hpp"
#include "ProblemInstance.hpp"

class Evaluator{
public:
	Evaluator();
	Evaluator(ProblemInstance p);

	int evaluate_solution(Solution);
	int evaluate_by_graph(Graph);

	bool testa_solucao(Solution);

	void set_instance(ProblemInstance);
	void set_solution(Solution);

	void print();

private:
	ProblemInstance instance;
	Solution solution;

	vector<int> realTimes;
	vector<int> expectedTimes;

	int total_atraso;
};

#endif