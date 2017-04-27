#ifndef SIMULATEDANNEALING_HPP
#define SIMULATEDANNEALING_HPP

#include <cmath>
#include "Movement.hpp"

using namespace twtjssp;

class SimulatedAnnealing : public Movement {

public:
    SimulatedAnnealing();
    SimulatedAnnealing(Solution);

    virtual Solution apply();

private:

    double alpha;
    float temperatura;
    float temperaturaInicial;
    float temperaturaFinal;
    int maxIteracoes;

    const float boltzmann = 1.38064852;
    const float euler = 2.718281;
};

#endif