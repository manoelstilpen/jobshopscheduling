//
// Created by manoel on 28/07/18.
//

#ifndef JOBSHOPSCHEDULING_SMARTVARIABLENEIGHBORHOODSEARCH_H
#define JOBSHOPSCHEDULING_SMARTVARIABLENEIGHBORHOODSEARCH_H

#include "Commons.hpp"

#include "FirstImprovement.hpp"
#include "ShakeK.hpp"
#include "Metaheuristic.hpp"

using namespace twtjssp;

class SmartVariableNeighborhoodSearch : public Metaheuristic {

public:
    SmartVariableNeighborhoodSearch();
    SmartVariableNeighborhoodSearch(Solution);

    virtual Solution apply();
    virtual void print_method_informations();

private:

    vector<Metaheuristic*> vizinhancas;

};

#endif //JOBSHOPSCHEDULING_SMARTVARIABLENEIGHBORHOODSEARCH_H
