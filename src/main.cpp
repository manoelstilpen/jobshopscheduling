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

    cout << "[BEGIN EXECUTION]" << endl;

    if(!Config::parseArguments(argc, argv)){
        exit(EXIT_FAILURE);
    }

    if(!ProblemInstance::load_instance(Config::instancePath)){
        exit(EXIT_FAILURE);
    }
    //ProblemInstance::print();

    RandGen::setSeed(Config::seed);
    RandGen::printSeed();

auto start = steady_clock::now();

    Solution solution;
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

    double elapsed_secs = duration_cast<milliseconds>(end - start).count();

    cout << elapsed_secs << " ms => " << elapsed_secs/1000.f << " s" << endl;
    cout << "[END EXECUTION]" << endl << endl;

	return 0;
}
