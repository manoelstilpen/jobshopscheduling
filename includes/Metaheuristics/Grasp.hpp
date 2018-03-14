#ifndef GRASP_HPP
#define GRASP_HPP

#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "FirstImprovement.hpp"
#include "Constructives.hpp"
#include "Metaheuristic.hpp"

#include <functional>

using namespace twtjssp;

class Grasp : public Metaheuristic {

public:
    Grasp();
    Grasp(ProblemInstance instance, double _alpha = 0);

	virtual Solution apply();	/*!< applies the grasp method */
	virtual Solution refinement(Solution&);
	virtual void print();
	virtual void print_graphic();
	virtual void print_method_informations();

protected:

	Metaheuristic* local_search;
	Constructive* constructive;

    double alpha;   			/*!< defines how greedy will be your grasp  */

};

#endif