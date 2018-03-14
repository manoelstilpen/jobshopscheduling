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
#include <Constructives/MOD.hpp>

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

bool argParse(int argc, char* argv[], string* method, int* repeat, double* alpha,
              string* path, bool* print, bool* printStats){

    po::options_description desc("Usage");
    desc.add_options()

            ("help,h", po::value< std::string >()->implicit_value("")->notifier(
                    [&desc](const std::string& topic) {
                        show_help(desc, topic);
                    }
            ),"Show help.")
            ("instance,i", po::value<string>(), "Instance path")
            ("alpha,a", po::value<double>()->default_value(*alpha))
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

    if(args.count("alpha")){
        *alpha = args["alpha"].as<double>();
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

    string instance_name = "bierwirth.txt";
    double alpha = 0.4;
    int repeat = 1;
	string method = "vns";
	bool printGantt = false;
	bool printStats = false;

    long seed = time(NULL);
    //long seed = 1516644548;    
    cout << "Seed = " << seed << endl;
	srand(seed);

	if(!argParse(argc, argv, &method, &repeat, &alpha, &instance_name, &printGantt, &printStats)){
		exit(EXIT_FAILURE);
	}

	Solution solution;
	ProblemInstance instance;
	instance.set_name_file(instance_name);
	if(!instance.load_instance()){
		exit(EXIT_FAILURE);
	}
	//instance.print();

clock_t begin = clock();

    if(method.compare("vns") == 0){
        // teste vns
        ConstructiveGraph constructiveGraph(instance, alpha);
        solution = constructiveGraph.apply();

        VariableNeighborhoodSearch vns(solution);
        solution = vns.apply();
        vns.print();
    }

    if(method.compare("grasp") == 0){
        // teste grasp
        Grasp grasp(instance, alpha);
        solution = grasp.apply();
        grasp.print();
    }

    if(method.compare("cons") == 0){
        // teste construtivo
        Constructive* cons = new ASPRT(instance, alpha);
        Solution s = cons->apply();
        cons->print();
    }


    // teste simulated annealing
 /*   ConstructiveGraph cons(instance, 0.1);
    Solution s = cons.apply();

    SimulatedAnnealing sa(s);
    solution = sa.apply();
    sa.print();
*/
clock_t end = clock();
double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

cout << "Tempo: " << elapsed_secs << endl << endl;

	return 0;
}
