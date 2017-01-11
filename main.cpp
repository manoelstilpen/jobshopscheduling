#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "ConstructiveGreedy.hpp"
#include "DeltaMoves/DeltaMoveExchange.hpp"
#include "DeltaMoves/DeltaMoveOpt1.hpp"
#include "Evaluator.hpp"
#include "Grasp.hpp"

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

	Grasp grasp(instance, 1);
	grasp.set_repeat(1);
	solution = grasp.apply_grasp();

/*
	ConstructiveGreedy constructive;
	constructive.set_instance(instance);
	solution = constructive.generate_solution();
*/
//	printSolution(10, 10, solution);


	//Evaluator evaluator(solution, instance);
	//evaluator.evaluateSolution();

	return 0;
}