#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "Constructives/Constructives.hpp"
#include "Movements/Movements.hpp"
#include "Evaluator.hpp"

#include <stdlib.h>     /* atof */
#include <unistd.h>		/* getopt */

int main(int argc, char** argv){

//	string instance_name = "abz6_f13.txt";
//	string instance_name = "instance.txt";
	string instance_name = "bierwirth.txt";
	double alpha_grasp = 0;
	int repeat = 1;
	string modo = "graph";

	int opt;
	while ((opt = getopt(argc, argv, "i:a:m:r:")) != -1) {
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
	instance.print();

	if(modo.compare("sprt") == 0){
		GraspSPRT grasp(instance, alpha_grasp);
		grasp.set_repeat(repeat);
		solution = grasp.apply();

//		grasp.print_graphic();
		grasp.print();
	} else if(modo.compare("priority") == 0){		
		GraspPriority grasp(instance, alpha_grasp);
		grasp.set_repeat(repeat);
		solution = grasp.apply();

		grasp.print_graphic();
		//grasp.print();
	} else if(modo.compare("mod") == 0){
		Grasp grasp(instance, alpha_grasp);
		grasp.set_repeat(repeat);
		solution = grasp.apply();

		grasp.print_graphic();
		//grasp.print();
	} else if(modo.compare("graph") == 0){
		
		/*Solution sol(instance);
		sol.extract_solution_from_file("Instances/solution-vitor-abz6.txt");
		sol.print_solution();
		Evaluator eval(instance);
		cout << eval.evaluate_by_graph(sol) << endl;
		VariableNeighborhoodSearch vns(sol);
		vns.apply();
		vns.print();*/

		//for(int i=0 ; i<10 ; i++){
			ConstructiveGraph constructive(instance);
			Solution solution = constructive.apply();
			VariableNeighborhoodSearch vns(solution);
			solution = vns.apply();
			vns.print();
		//}
	}

	return 0;
}
