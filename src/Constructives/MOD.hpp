//
// Created by manoel on 04/03/18.
//

#ifndef JOBSHOPSCHEDULING_MOD_HPP
#define JOBSHOPSCHEDULING_MOD_HPP

#include "Constructive.hpp"

class MOD : public Constructive {

    MOD(ProblemInstance instance, double alpha);

    virtual void print_method_informations();
    virtual float define_priority(Schedule op);
    virtual int choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts);

};

#endif //JOBSHOPSCHEDULING_MOD_HPP
