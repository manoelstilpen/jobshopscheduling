#ifndef CONSTRUCTIVE_GRAPH_HPP
#define CONSTRUCTIVE_GRAPH_HPP

#include "Commons.hpp"
#include "ProblemInstance.hpp"
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

        void set_alpha(double);

    private:
        Graph graph;
        double alpha;
        ProblemInstance instance;
};

#endif
