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

auto start = steady_clock::now();

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
        solution = cons->apply();
        cons->print();
    }

    if(Config::method == "sa"){
        ConstructiveGraph cons(Config::alpha);
        solution = cons.apply();

        SimulatedAnnealing sa(solution);
        solution = sa.apply();
        sa.print();
    }

auto end = steady_clock::now();

    auto elapsed_secs = duration_cast<milliseconds>(end - start).count();

    cout << elapsed_secs << " ms" << endl;
	return 0;
}
