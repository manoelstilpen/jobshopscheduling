#ifndef ASPRT_HPP
#define ASPRT_HPP

#include "../Commons.hpp"
#include "../Metaheuristics/Grasp.hpp"

using namespace twtjssp;

class ASPRT : public Constructive {

public:

    ASPRT(ProblemInstance instance, double _alpha = 0);

    virtual void print_method_informations();
    virtual float define_priority(Schedule op);
    virtual int choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts);

};

#endif