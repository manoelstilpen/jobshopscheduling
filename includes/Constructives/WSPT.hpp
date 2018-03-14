#ifndef WSPT_HPP_
#define WSPT_HPP_

#include "Commons.hpp"
#include "Constructive.hpp"

using namespace twtjssp;

class WSPT : public Constructive {

public:
    WSPT();
    WSPT(ProblemInstance p, double _alpha);

    virtual void print_method_informations();
    virtual float define_priority(Schedule op); /*!< method used to evaluate a schedule */
    virtual int choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts);
    //virtual float valor_grasp(const float& min, const float& max); 

private:

};

#endif