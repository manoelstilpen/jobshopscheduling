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

	Solution apply_grasp1();
	Solution apply_grasp2();

	Solution alocaTarefa(Solution* solution, Schedule tarefa);

	void set_alpha(double);
	void set_instance(ProblemInstance);
	void set_repeat(int);

	int get_atraso();

	void print();
	void print_graph();
	void print_partial();

private:
	ProblemInstance instance;
	ScheduleMatrix jobs;
	Solution solution;
	Evaluator evaluator;

	double alpha;
	int repeat;
	int media_atraso;

	struct Custo{
		int job;
		int task;
		int indice;
		int custo;

		Custo(){
			job = task = indice = custo = 0;
		}

		Custo(int j, int t, int i, int c){
			this->job = j;
			this->task = t;
			this->indice = i;
			this->custo = c;
		}
	};
};

#endif