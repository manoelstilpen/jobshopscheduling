#ifndef CONSTRUCTIVE_GRAPH_HPP
#define CONSTRUCTIVE_GRAPH_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "../Metaheuristics/Grasp.hpp"
#include "Constructives.hpp" 

// CONJUNCAO => e
// DISJUNCAO => ou

class ConstructiveGraph : public Constructive {
    
    public:
        ConstructiveGraph();
        ConstructiveGraph(ProblemInstance, double);
        virtual Solution apply();
        virtual void print_method_informations();

        virtual void print();
        void print_gantt();

    private:
        Graph graph;
        double alpha;

};

#endif
