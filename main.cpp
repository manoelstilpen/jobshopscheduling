#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "ConstructiveGreedy.hpp"
#include "DeltaMoves/DeltaMoveExchange.hpp"
#include "DeltaMoves/DeltaMoveOpt1.hpp"
#include "Evaluator.hpp"
#include "Grasp.hpp"

#include <stdlib.h>     /* atof */
#include <unistd.h>

int main(int argc, char** argv){

	int opt;
	string instance_name = "abz5_f13.txt";
	double alpha_grasp = 0.5;

	while ((opt = getopt(argc, argv, "i:a:")) != -1) {
		switch(opt){
			case 'i':{
				// instance name
				instance_name = optarg;
			}break;

			case 'a':{
				// alpha value
				alpha_grasp = atof(optarg);
			}break;
		}
	}

	srand ( time(NULL) );

	Solution solution;

	ProblemInstance instance;
	instance.set_name_file(instance_name);
	if(!instance.load_instance()){
		exit(EXIT_FAILURE);
	}
	//instance.print();

	int nJobs = instance.get_num_jobs();
	int nTasks = instance.get_num_tasks();
	int nMachines = instance.get_num_machines();

	Grasp grasp(instance, alpha_grasp);
	grasp.set_repeat(10);
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