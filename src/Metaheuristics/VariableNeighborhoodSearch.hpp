#ifndef VNS_HPP_
#define VNS_HPP_

#include "../Commons.hpp"

#include "../LocalSearches/FirstImprovement.hpp"
#include "../LocalSearches/ShakeK.hpp"
#include "Metaheuristic.hpp"

using namespace twtjssp;

class VariableNeighborhoodSearch : public Metaheuristic {

public:
    VariableNeighborhoodSearch();
    VariableNeighborhoodSearch(Solution);

    virtual Solution apply();
    virtual void print_method_informations();

private:

    vector<Metaheuristic*> vizinhancas;
    
};

#endif