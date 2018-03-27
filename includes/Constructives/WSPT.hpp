#ifndef WSPT_HPP_
#define WSPT_HPP_

#include "Commons.hpp"
#include "Constructive.hpp"

using namespace twtjssp;

class WSPT : public Constructive {

public:
    explicit WSPT(double _alpha);

    void print_method_informations() override;
    float define_priority(Schedule op) override; /*!< method used to evaluate a schedule */
    //virtual float valor_grasp(const float& min, const float& max);

};

#endif