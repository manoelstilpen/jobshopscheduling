#ifndef CONSTRUCTIVE_GRAPH_HPP
#define CONSTRUCTIVE_GRAPH_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "Grasp.hpp"

#define GHOSTNODES 2
#define INITNODE 1

// CONJUNCAO => e
// DISJUNCAO => ou

class ConstructiveGraph : public Constructive{
    
    public:
        ConstructiveGraph();
        ConstructiveGraph(ProblemInstance);
        virtual Solution apply();

        vector<vector<Edge>> bellmanFord();

        virtual void print();
        void printDistances(int dist[], int n);

    private:
        Graph graph;
        int vertexPerJob;

};

#endif