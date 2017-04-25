#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Commons.hpp"
#include "ProblemInstance.hpp"

using namespace twtjssp;

class Graph{

public:

    Edge operator[](const int& i){
        return (edges[i]);
    }

    Graph();
    Graph(ProblemInstance);

    vector<vector<Edge>> bellmanFord();

    void add(Edge);
    void invert(int);

    void printDistances();
    GanttRepresentation generate_gantt();

    int size();

    void setNVertex(int);
    void setInstance(ProblemInstance);

    int getVertexPerJob();
    vector<int> getDistances();
    int getDistanceFrom(int, int);


private:
    ProblemInstance instance;
    int vertexPerJob;
    int nVertex;
    int nEdges;

    vector<Edge> edges;
    vector<int> distances;
};

#endif