#ifndef CEI_HPP_
#define CEI_HPP_

#include "Movements.hpp"
#include "../Commons.hpp"
#include "../Solution.hpp"

using namespace twtjssp;

class CEI : public Movement {

public:

    CEI(Solution);
    CEI();

    virtual Solution apply();
    virtual void updateCouldMove();


private:

    vector< vector<Edge> > couldMove;

};

#endif