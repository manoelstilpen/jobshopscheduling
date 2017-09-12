#ifndef CET2MT_HPP_
#define CET2MT_HPP_

#include "../Commons.hpp"
#include "Movement.hpp"

using namespace twtjssp;

class CET2MT : public Movement {

public:
    CET2MT();
    CET2MT(Solution);

    virtual Solution apply();
    virtual void print_method_informations();

};


#endif