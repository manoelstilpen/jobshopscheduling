#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "Constructives/Constructives.hpp"
#include "LocalSearches/LocalSearches.hpp"
#include "Metaheuristics/Metaheuristics.hpp"
#include "Evaluator.hpp"

#include <iostream>
#include <chrono>
#include <boost/program_options.hpp>

#include <stdlib.h>     /* atof */
#include <unistd.h>		/* getopt */

using namespace std;
using namespace std::chrono;
namespace po = boost::program_options;

void show_help(const po::options_description& desc, const std::string& topic = ""){
    std::cout << desc << '\n';
    if (topic != "") {
        std::cout << "You asked for help on: " << topic << '\n';
    }
    exit(EXIT_SUCCESS);
}

bool argParse(int argc, char* argv[], string* method, int* repeat, string* path, bool* print, bool* printStats){
    po::options_description desc("Usage");
    desc.add_options()
        ("help,h", po::value< std::string >()->implicit_value("")->notifier(
            [&desc](const std::string& topic) {
                show_help(desc, topic);
            }
        ),"Show help.")
        ("instance,i", po::value<string>(), "Instance path")
        ("method,m", po::value<string>()->default_value("grasp"), "(Optional) Specify the constructive method to use")
		("repeat,r", po::value<int>()->default_value(1), "(Optional) Specify how many times run the program")
		("print,p", "(Optional) If enabled program will print Gantt graphic")
		("stats,s", "(Optional) If enabled program will print execution stats");

    if (argc == 1) {
        show_help(desc);
        return false;
    }

    po::variables_map args;

    try {
        po::store(po::parse_command_line(argc, argv, desc), args);
    } catch (po::error const& e) {
        std::cerr << e.what() << '\n';
        return false;
    }
    po::notify(args);

    *method = args["method"].as<string>();

	if(args.count("repeat")){
		*repeat = args["repeat"].as<int>();
	}

    if(args.count("print")){
        *print = true;
	}
	
	if(args.count("stats")){
		*printStats = true;
	}

    if(args.count("instance")){
        *path = args["instance"].as<string>();
    } else {
        cerr << "Instance parameter is required" << endl << endl;
        show_help(desc);
        return false;
    }

    return true;
}

int main(int argc, char** argv){

//	string instance_name = "abz6_f13.txt";
//	string instance_name = "instance.txt";
	string instance_name = "bierwirth.txt";
	double alpha_grasp = 0;
	int repeat = 1;
	string movement = "vns";
	bool printGantt = false;
	bool printStats = false;

	srand(time(NULL));

	if(!argParse(argc, argv, &movement, &repeat, &instance_name, &printGantt, &printStats)){
		exit(EXIT_FAILURE);
	}

	Solution solution;
	ProblemInstance instance;
	instance.set_name_file(instance_name);
	if(!instance.load_instance()){
		exit(EXIT_FAILURE);
	}
//	instance.print();

clock_t begin = clock();

	ConstructiveGraph constructive(instance, alpha_grasp);
	solution = constructive.apply();

	VariableNeighborhoodSearch vns(solution);
	solution = vns.apply();
	vns.print_graphic();

clock_t end = clock();
double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

//cout << elapsed_secs << endl;

	return 0;
}
