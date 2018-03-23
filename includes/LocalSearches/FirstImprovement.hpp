#ifndef FIRSTIMPROVEMENT_HPP
#define FIRSTIMPROVEMENT_HPP

#include "Metaheuristic.hpp"

using namespace twtjssp;

class FirstImprovement : public Metaheuristic {

public:

    explicit FirstImprovement(Solution);
    FirstImprovement() = default;

    Solution apply() override;
    void print_method_informations() override;
};

#endif