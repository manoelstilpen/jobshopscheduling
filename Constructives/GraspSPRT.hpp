#ifndef GRASPSPRT_HPP
#define GRASPSPRT_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "../Solution.hpp"
#include "Grasp.hpp"

#include <iostream>
#include <functional>

class GraspSPRT : public Grasp {

public:
    GraspSPRT();
    GraspSPRT(ProblemInstance p, double alpha=0, bool _r = true);

    virtual float define_priority(Schedule);
//    virtual int choose_schedule();
    virtual void print_graphic();
    virtual void print_method_informations();
};

#endif