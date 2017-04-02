#ifndef CONSTRUCTIVE_GRAPH_HPP
#define CONSTRUCTIVE_GRAPH_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "Grasp.hpp"

#define GHOSTNODES 2
#define INITNODE 1

// CONJUNCAO => e
// DISJUNCAO => ou

class ConstructiveGraph{
    
    public:
        ConstructiveGraph();
        void construct();

        vector<vector<Edge>> bellmanFord();

        void print();
        void printDistances(int dist[], int n);
        void setInstance(ProblemInstance);

    private:
        Graph graph;
        ProblemInstance instance;

        int vertexPerJob;

};

#endif