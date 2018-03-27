//
// Created by manoel on 04/03/18.
//

#ifndef JOBSHOPSCHEDULING_MOD_HPP
#define JOBSHOPSCHEDULING_MOD_HPP

#include "Constructive.hpp"

class MOD : public Constructive {

public:
    MOD(double alpha);

    void print_method_informations() override;
    float define_priority(Schedule op) override;

};

#endif //JOBSHOPSCHEDULING_MOD_HPP
