//
// Created by manoel on 14/03/18.
//

#ifndef JOBSHOPSCHEDULING_CRITICALPATH_HPP
#define JOBSHOPSCHEDULING_CRITICALPATH_HPP

#include <ProblemInstance.hpp>
#include "Commons.hpp"

#include <map>

using namespace twtjssp;

class CriticalPath {

public:

    CriticalPath(){
        nVertex = (ProblemInstance::getNumOperations()+GHOSTNODES)*ProblemInstance::getNumJobs()+ INITNODE;
        vertexPerJob = ProblemInstance::getNumOperations() + GHOSTNODES;
    }

    virtual vector<Edge> getCriticalPath(map<int, vector<Node>>, map<int, Node>, vector<int>&) = 0;

protected:

    int nVertex;
    int vertexPerJob;
};

#endif //JOBSHOPSCHEDULING_CRITICALPATH_HPP
