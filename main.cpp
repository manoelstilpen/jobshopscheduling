#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "Constructives/ConstructiveGreedy.hpp"
#include "Constructives/Grasp.hpp"
#include "DeltaMoves/DeltaMoveExchange.hpp"
#include "DeltaMoves/DeltaMoveOpt1.hpp"
#include "Evaluator.hpp"

#include <stdlib.h>     /* atof */
#include <unistd.h>		/* getopt */

int main(int argc, char** argv){

	int opt;
	string instance_name = "abz5_f13.txt";
	double alpha_grasp = 0.5;
	int repeat = 1;
	string modo = "grasp";

	while ((opt = getopt(argc, argv, "i:a:m:")) != -1) {
		switch(opt){
			case 'i':{
				// instance name
				instance_name = optarg;
			}break;

			case 'a':{
				// alpha value
				alpha_grasp = atof(optarg);
			}break;

			case 'm':{
				// constructive mode
				modo = optarg;
			}break;

			case 'r':{
				// repeat times
				repeat = atoi(optarg);
			}

		}
	}

	srand(time(NULL));

	Solution solution;
	// instance load
	ProblemInstance instance;
	instance.set_name_file(instance_name);
	if(!instance.load_instance()){
		exit(EXIT_FAILURE);
	}
	//instance.print();

	int nJobs = instance.get_num_jobs();
	int nTasks = instance.get_num_tasks();
	int nMachines = instance.get_num_machines();

	if(modo.compare("grasp") == 0){
		Grasp grasp(instance, alpha_grasp);
		grasp.set_repeat(repeat);
		solution = grasp.apply_grasp();
		//grasp.print_graph();
		grasp.print();
	} else if(modo.compare("greedy") == 0){
		ConstructiveGreedy greedy(instance, alpha_grasp);
		greedy.set_repeat(repeat);
		solution = greedy.generate_solution();
		//greedy.print_graph();
		greedy.print();

	}

//	printSolution(10, 10, solution);


	return 0;
}