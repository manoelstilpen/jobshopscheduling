#ifndef GRASP_PRIORITY_HPP
#define GRASP_PRIORITY_HPP

#include "Grasp.hpp"

class GraspPriority : public Grasp {

public:
    GraspPriority();
    GraspPriority(ProblemInstance, double _a = 0);

    virtual float define_priority(Schedule);
    virtual int choose_schedule();
    virtual void print_graphic();
    virtual void print_method_informations();

};

#endif
