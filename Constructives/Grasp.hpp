#ifndef GRASP_HPP
#define GRASP_HPP

#include "Constructive.hpp"
#include "../Commons.hpp"
#include "../ProblemInstance.hpp"

using namespace twtjssp;

class Grasp : public Constructive {

public:
    Grasp();
    Grasp(ProblemInstance instance, double _alpha = 0);

    virtual Solution apply();
    virtual float define_priority(Schedule op);

protected:

    double alpha;

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