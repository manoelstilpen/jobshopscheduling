#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "ConstructiveGreedy.hpp"
#include "DeltaMoves/DeltaMoveExchange.hpp"
#include "DeltaMoves/DeltaMoveOpt1.hpp"
#include "Evaluator.hpp"

#include <ctime>

int main(){

	srand ( time(NULL) );

	Solution solution;

	ProblemInstance instance;
	instance.set_name_file("abz5_f13.txt");
	instance.load_instance();
	instance.print();

	int nJobs = instance.get_num_jobs();
	int nTasks = instance.get_num_tasks();
	int nMachines = instance.get_num_machines();

	ConstructiveGreedy constructive;
	constructive.set_instance(instance);
	solution = constructive.generate_solution();

	// exchange move
	for(int i=0 ; i<10 ; i++){
		cout << rand() % nMachines << endl;
		DeltaMoveExchange exchange(solution, rand() % nMachines, rand() % nTasks, rand() % nTasks);
		solution = exchange.apply_exchange_move();
	}

	// opt1 move
	for(int i=0 ; i<10 ; i++){
		DeltaMoveOpt1 opt1(solution, rand() % nMachines, rand() % nTasks, rand() % nTasks);
		solution = opt1.apply_opt1_move();
	}

//	printSolution(10, 10, solution);

	Evaluator evaluator(solution, instance);
	evaluator.evaluateSolution();

	return 0;
}