//
// Created by manoel on 14/03/18.
//

#ifndef JOBSHOPSCHEDULING_BELLMANFORD_HPP
#define JOBSHOPSCHEDULING_BELLMANFORD_HPP

#include "CriticalPath.hpp"
#include "Commons.hpp"

#include <map>

using namespace twtjssp;

class BellmanFord : public CriticalPath {

public:
    BellmanFord();

    vector<Edge> getCriticalPath(map<int, vector<Node> >& graph,
                                 map<int, Node>& vertexList,
                                 vector<int>& distances) override;

};

#endif //JOBSHOPSCHEDULING_BELLMANFORD_HPP
