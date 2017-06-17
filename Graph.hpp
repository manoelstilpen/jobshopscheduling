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

    vector< vector<Edge> > bellmanFord();

    void add(Edge);
    void invert(int);

    void printDistances();
    void printCriticalPath();
    void printEdges();

    Graph construct_conjuctive_graph();
    Graph construct_disjuntive_graph(GanttRepresentation);

    GanttRepresentation generate_gantt();
    Graph generate_graph(GanttRepresentation);

    int size();

    void setNVertex(int);
    void set_instance(ProblemInstance);

    int getVertexPerJob();
    vector<int> getDistances();
    int getDistanceFrom(int, int);

    bool verifyFeasibility();


private:
    ProblemInstance instance;
    int vertexPerJob;
    int nVertex;
    int nEdges;

    vector<Edge> edges;
    vector<int> distances;
    vector< vector<Edge> > criticalPath;
};

#endif