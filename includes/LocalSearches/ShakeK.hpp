#ifndef SHAKE_HPP
#define SHAKE_HPP

#include "Commons.hpp"
#include "Metaheuristic.hpp"
#include <unistd.h>

using namespace twtjssp;

class ShakeK : public Metaheuristic {

public:

    ShakeK();
    ShakeK(Solution, int);

    virtual Solution apply();

    void setKMoves(int);

private:

    int k_moves;

};

#endif