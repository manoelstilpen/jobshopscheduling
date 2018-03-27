#ifndef SPRT_HPP
#define SPRT_HPP

#include "Commons.hpp"
#include "Constructives.hpp"

using namespace twtjssp;

class SPRT : public Constructive {

public:

    explicit SPRT(double _alpha);

    void print_method_informations() override;
    float define_priority(Schedule op) override; /*!< method used to evaluate a schedule */
};

#endif