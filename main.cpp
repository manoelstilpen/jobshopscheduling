#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "Constructives/Constructives.hpp"
#include "Evaluator.hpp"

#include <stdlib.h>     /* atof */
#include <unistd.h>		/* getopt */

int main(int argc, char** argv){

//	string instance_name = "abz5_f13.txt";
//	string instance_name = "instance.txt";
	string instance_name = "bierwirth.txt";
	double alpha_grasp = 0;
	int repeat = 1;
	string modo = "sprt";

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
	//instance.print();

	if(modo.compare("sprt") == 0){
		GraspSPRT grasp(instance, alpha_grasp);
		grasp.set_repeat(repeat);
		solution = grasp.apply();

		grasp.print_graphic();
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
		grasp.print();
	}

	return 0;
}