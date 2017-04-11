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

	int analisa_job(Schedule, Solution, float);
	int analisa_machine(Schedule, Solution);
	bool testa_solucao(Solution);

	void set_instance(ProblemInstance);
	void set_solution(Solution);

	void print();
	void print_graph();

private:
	ProblemInstance instance;
	Solution solution;

	vector<int> realTimes;
	vector<int> expectedTimes;

	int total_atraso;
};

#endif