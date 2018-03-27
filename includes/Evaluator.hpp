#ifndef EVALUATOR
#define EVALUATOR

#include "Commons.hpp"
#include "Solution.hpp"
#include "ProblemInstance.hpp"

class Evaluator{
public:
	Evaluator();

	int evaluate_solution(Solution);
	int evaluate_by_graph(Graph);
	int evaluate_by_graph(Solution);

	bool testa_solucao(Solution);

	void print();

private:

	vector<int> realTimes;
	vector<int> expectedTimes;

	int total_atraso;
};

#endif