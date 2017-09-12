#ifndef FIRSTIMPROVEMENT_HPP
#define FIRSTIMPROVEMENT_HPP

#include "Movement.hpp"

using namespace twtjssp;

class FirstImprovement : public Movement {

public:

    FirstImprovement(Solution);
    FirstImprovement();

    virtual Solution apply();
    virtual void print_method_informations();
};

#endif