#ifndef CONSTRUCTIVE_GRAPH_HPP
#define CONSTRUCTIVE_GRAPH_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "Constructives.hpp" 

using namespace twtjssp;

// CONJUNCAO => e
// DISJUNCAO => ou

class ConstructiveGraph {
    
    public:
        ConstructiveGraph();
        ConstructiveGraph(ProblemInstance, double);
        virtual Solution apply();
        virtual void print_method_informations();

        virtual void print();
        void print_gantt();

    private:
        ProblemInstance instance;
        Graph graph;
        double alpha;

};

#endif
