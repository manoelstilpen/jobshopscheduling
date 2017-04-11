#ifndef GRASP_HPP
#define GRASP_HPP

#include "Constructive.hpp"
#include "../Commons.hpp"
#include "../ProblemInstance.hpp"

using namespace twtjssp;

/**
 * Class used to define a GRASP method, you can override his methods to create your own grasp
 */

class Grasp : public Constructive {

public:
    Grasp();
    Grasp(ProblemInstance instance, double _alpha = 0);

    virtual Solution apply();                   /*!< applies the grasp method */
    virtual float define_priority(Schedule op); /*!< method used to evaluate a schedule */

    float valor_grasp(int min, int max);        /*!< returns the value which defines the operation's restrict list */

protected:

    double alpha;   /*!< defines how greedy will be your grasp  */

    struct Custo{
		int job;
		int task;
		int indice;
		float custo;

		Custo(){
			job = task = indice = custo = 0;
		}

		Custo(int j, int t, int i, float c){
			this->job = j;
			this->task = t;
			this->indice = i;
			this->custo = c;
		}
	};

};

#endif