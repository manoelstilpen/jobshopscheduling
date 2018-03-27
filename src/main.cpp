#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "Constructives/Constructives.hpp"
#include "LocalSearches/LocalSearches.hpp"
#include "Metaheuristics/Metaheuristics.hpp"

#include "Evaluator.hpp"
#include <RandGen.hpp>

#include <Config.hpp>
#include <iostream>

#include <chrono>
#include <stdlib.h>     /* atof */
#include <unistd.h>		/* getopt */

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){

    if(!Config::parseArguments(argc, argv)){
        exit(EXIT_FAILURE);
    }

    Solution solution;
    if(!ProblemInstance::load_instance(Config::instancePath)){
        exit(EXIT_FAILURE);
    }
    //ProblemInstance::print();

    RandGen::setSeed(Config::seed);
    RandGen::printSeed();

clock_t begin = clock();

    if(Config::method == "vns"){
        // teste vns
        ConstructiveGraph constructiveGraph(Config::alpha);
        solution = constructiveGraph.apply();

        VariableNeighborhoodSearch vns(solution);
        solution = vns.apply();
        vns.print();
    }

    if(Config::method == "grasp"){
        // teste grasp
        Grasp grasp(Config::alpha);
        solution = grasp.apply();
        grasp.print();
    }

    if(Config::method == "cons"){
        // teste construtivo
        Constructive* cons = new ASPRT(Config::alpha);
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
