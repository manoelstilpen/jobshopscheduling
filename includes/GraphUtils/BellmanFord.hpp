//
// Created by manoel on 14/03/18.
//

#ifndef JOBSHOPSCHEDULING_BELLMANFORD_HPP
#define JOBSHOPSCHEDULING_BELLMANFORD_HPP

#include "CriticalPath.hpp"
#include "Commons.hpp"

using namespace twtjssp;

class BellmanFord : public CriticalPath {

    vector<Edge> getCriticalPath();

};

#endif //JOBSHOPSCHEDULING_BELLMANFORD_HPP
