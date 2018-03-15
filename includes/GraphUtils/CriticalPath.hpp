//
// Created by manoel on 14/03/18.
//

#ifndef JOBSHOPSCHEDULING_CRITICALPATH_HPP
#define JOBSHOPSCHEDULING_CRITICALPATH_HPP

#include <ProblemInstance.hpp>
#include "Commons.hpp"

using namespace twtjssp;

class CriticalPath {

public:

    virtual vector<Edge> getCriticalPath() = 0;

protected:

    ProblemInstance instance;

};

#endif //JOBSHOPSCHEDULING_CRITICALPATH_HPP
