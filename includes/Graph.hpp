#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <Commons.hpp>
#include <ProblemInstance.hpp>
#include <GraphUtils/CriticalPath.hpp>
#include <GraphUtils/BellmanFord.hpp>
#include <GraphUtils/TopologicalSort.hpp>

#include <map>

using namespace twtjssp;

class Graph{

public:
    Graph();


    bool invert(Node, Node, bool store=true);

    bool isFeasible();

    Graph construct_conjunctive_graph();
    Graph construct_disjunctive_graph(GanttRepresentation);

    GanttRepresentation generate_gantt();

    void undo_last_movement();

    int getNEdges();
    int getVertexPerJob();
    int getDistanceFrom(int);
    int getWeight(int, int);
    int getVertexId(int, int);
    int getVertexId(Node);
    Node getVertex(int);
    Node getVertex(int, int);

    map<int, vector<Node > > getAdjacencyList();
    vector<Edge> getCriticalPath();
    vector< vector<Edge> > getCriticalBlocks();

    void printGraph();
    void printCriticalPath();
    void printCriticalBlock();

private:
    void add(Node);
    void add(Node, Node);
    void saveMovement(Edge);
    bool isFeasibleRec(Node, vector<bool>&, vector<bool>&);

    int vertexPerJob;
    int nVertex;

    int nEdges;

    CriticalPath* criticalPathMethod;

    map<int, vector<Node > > edges;
    map<int, Node> vertexList;

    vector<Edge> criticalPath;
    vector<Edge> lastMovements;
    vector<int> distances;
    vector<int> path;

    vector< vector<Edge> > criticalBlocks;

};

#endif