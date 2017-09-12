#ifndef BEST_IMPROVEMENT_HPP
#define BEST_IMPROVEMENT_HPP

#include "Movement.hpp"
#include "../Solution.hpp"
#include "../Commons.hpp"

using namespace twtjssp;

class BestImprovement : public Movement {

public:
    BestImprovement();
    BestImprovement(Solution);

    virtual Solution apply();
    virtual void print_method_informations();

};

#endif