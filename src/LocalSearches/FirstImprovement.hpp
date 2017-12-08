#ifndef FIRSTIMPROVEMENT_HPP
#define FIRSTIMPROVEMENT_HPP

#include "../Metaheuristics/Metaheuristic.hpp"

using namespace twtjssp;

class FirstImprovement : public Metaheuristic {

public:

    FirstImprovement(Solution);
    FirstImprovement();

    virtual Solution apply();
    virtual void print_method_informations();
};

#endif