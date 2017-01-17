#ifndef EVALUATOR
#define EVALUATOR

#include "Commons.hpp"
#include "ProblemInstance.hpp"

class Evaluator{
public:
	Evaluator();
	Evaluator(ProblemInstance p);
	Evaluator(Solution s, ProblemInstance p);

	int evaluate_solution(Solution);
	int analisa_job(Schedule, Solution);
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