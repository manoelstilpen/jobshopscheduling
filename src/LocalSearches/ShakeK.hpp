#ifndef SHAKE_HPP
#define SHAKE_HPP

#include "../Commons.hpp"

#include "../Metaheuristics/Metaheuristic.hpp"

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