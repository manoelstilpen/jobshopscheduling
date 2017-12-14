#ifndef SPRT_HPP
#define SPRT_HPP

#include "../Commons.hpp"
#include "Constructives.hpp"

using namespace twtjssp;

class SPRT : public Constructive {

public:
    SPRT();
    SPRT(ProblemInstance p, double _alpha);

    virtual void print_method_informations();
    virtual float define_priority(Schedule op); /*!< method used to evaluate a schedule */
    virtual int choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts);
};

#endif