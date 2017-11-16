#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Commons.hpp"
#include "ProblemInstance.hpp"

#include <map>

using namespace twtjssp;

class Graph{

public:
    Graph();
    Graph(ProblemInstance);

    void set_instance(ProblemInstance);

    void invert(int, int);
    void invert(Node, Node);

    vector< pair<Node, Node> > bellmanFord();
    bool isFeasible(vector<int>);

    Graph construct_conjuctive_graph();
    Graph construct_disjuntive_graph(GanttRepresentation);

    int getNEdges();
    int getVertexPerJob();
    int getDistanceFrom(int);

    void printGraph();
    
private:

    void add(Node);
    void add(Node, Node, EdgeData);
    void add(int, int);

    ProblemInstance instance;

    int vertexPerJob;
    int nVertex;
    int nEdges;

    map<int, vector< pair<Node, EdgeData> > > edges;
    map<int, Node> vertexList;

    vector<int> distances;

};

#endif