#ifndef CONSTRUCTIVE_GRAPH_HPP
#define CONSTRUCTIVE_GRAPH_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "Grasp.hpp"
#include "GraspPriority.hpp"
#include "Constructives.hpp"

// CONJUNCAO => e
// DISJUNCAO => ou

class ConstructiveGraph : public Constructive{
    
    public:
        ConstructiveGraph();
        ConstructiveGraph(ProblemInstance);
        virtual Solution apply();

        virtual void print();
        void print_gantt();

    private:
        Graph graph;

};

#endif
