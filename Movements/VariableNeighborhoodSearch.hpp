#ifndef VNS_HPP_
#define VNS_HPP_

#include "../Commons.hpp"
#include "Movements.hpp"

using namespace twtjssp;

class VariableNeighborhoodSearch : public Movement {

public:
    VariableNeighborhoodSearch();
    VariableNeighborhoodSearch(Solution);

    virtual Solution apply();
    virtual void print_method_informations();

private:
    int nVizinhancas;
    
};

#endif