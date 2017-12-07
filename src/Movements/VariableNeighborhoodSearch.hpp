#ifndef VNS_HPP_
#define VNS_HPP_

#include "../Commons.hpp"

#include "FirstImprovement.hpp"
#include "ShakeK.hpp"
#include "Movement.hpp"

using namespace twtjssp;

class VariableNeighborhoodSearch : public Movement {

public:
    VariableNeighborhoodSearch();
    VariableNeighborhoodSearch(Solution);

    virtual Solution apply();
    virtual void print_method_informations();

private:

    vector<Movement*> vizinhancas;
    
};

#endif