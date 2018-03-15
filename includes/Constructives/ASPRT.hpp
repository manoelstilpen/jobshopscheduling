#ifndef ASPRT_HPP
#define ASPRT_HPP

#include "Commons.hpp"
#include "Constructive.hpp"

using namespace twtjssp;

class ASPRT : public Constructive {

public:

    explicit ASPRT(double _alpha = 0);

    void print_method_informations() override;
    float define_priority(Schedule op) override;
    int choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts) override;

};

#endif