//
// Created by manoel on 22/03/18.
//

#ifndef JOBSHOPSCHEDULING_BESTIMPROVEMENT_HPP
#define JOBSHOPSCHEDULING_BESTIMPROVEMENT_HPP

#include <Commons.hpp>
#include <Metaheuristics/Metaheuristic.hpp>

class BestImprovement : public Metaheuristic {

public:

    explicit BestImprovement(Solution);
    BestImprovement() = default;

    Solution apply() override;
    void print_method_informations() override;

};


#endif //JOBSHOPSCHEDULING_BESTIMPROVEMENT_HPP
