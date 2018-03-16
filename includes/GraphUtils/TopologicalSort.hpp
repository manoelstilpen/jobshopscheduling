//
// Created by manoel on 15/03/18.
//

#ifndef JOBSHOPSCHEDULING_TOPOLOGICALSORT_HPP
#define JOBSHOPSCHEDULING_TOPOLOGICALSORT_HPP

#include <CriticalPath.hpp>

class TopologicalSort : public CriticalPath {

public:
    TopologicalSort();

    vector<Edge> getCriticalPath(map<int, vector<Node> > graph,
                                 map<int, Node> vertexList,
                                 vector<int>& distances) override;

private:

    void topologicalSortUtil(int v,
                             vector<bool>& visited,
                             stack<int>& stack,
                             map<int, vector<Node> > graph);

    vector<int> updateDistancesFromTopOrder(map<int, vector<Node> > graph,
                                     std::stack<int> order,
                                     vector<int>& distances,
                                     map<int, Node> vertexList);

    stack<int> topologicalSort(map<int, vector<Node> > graph,
                                vector<int> &distances);
};


#endif //JOBSHOPSCHEDULING_TOPOLOGICALSORT_HPP
