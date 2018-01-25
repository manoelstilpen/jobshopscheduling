#ifndef SIMULATEDANNEALING_HPP
#define SIMULATEDANNEALING_HPP

#include <cmath>
#include <unistd.h>
#include "Metaheuristic.hpp"

using namespace twtjssp;

class SimulatedAnnealing : public Metaheuristic {

public:
    SimulatedAnnealing();
    SimulatedAnnealing(Solution);

    virtual Solution apply();
    virtual void print_method_informations();

private:

    double alpha;
    float temperatura;
    float temperaturaInicial;
    float temperaturaFinal;
    int maxIteracoes;

    const float boltzmann = 1.3806e-5;
//    const float boltzmann = 1.38064852;
    const float euler = std::exp(1.0);
};

#endif