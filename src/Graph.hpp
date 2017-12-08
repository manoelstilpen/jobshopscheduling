#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Commons.hpp"
#include "ProblemInstance.hpp"

// rever imports
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <limits.h>

using namespace twtjssp;

class Graph{

public:
    Graph();
    Graph(ProblemInstance);

    void set_instance(ProblemInstance);

    bool invert(int, int);
    bool invert(Node, Node);

    vector< pair<Node, Node> > bellmanFord();
    vector<int> topologicalSort();
    bool isFeasible();

    Graph construct_conjunctive_graph();
    Graph construct_disjunctive_graph(GanttRepresentation);

    GanttRepresentation generate_gantt();

    int getNEdges();
    int getVertexPerJob();
    int getDistanceFrom(int);
    int getWeight(int, int);
    int getVertexId(int, int);
    int getVertexId(Node);
    Node getVertex(int);
    Node getVertex(int, int);

    map<int, vector<Node > > getAdjacencyList();
    vector< pair<Node, Node> > getCriticalPath();

    void printGraph();
    void printCriticalPath();
    
private:

    void add(Node);
    void add(Node, Node);
    void add(int, int);

    bool isFeasibleRec(Node, vector<bool>&, vector<bool>&);
    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& stack);
    void updateDistancesFromTopOrder(stack<int>);
  
    ProblemInstance instance;

    int vertexPerJob;
    int nVertex;
    int nEdges;

    map<int, vector<Node > > edges;
    map<int, Node> vertexList;

    vector< pair<Node, Node> > criticalPath;
    vector<int> distances;
    vector<int> path;

};

#endif