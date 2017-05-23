#ifndef GRASP_HPP
#define GRASP_HPP

#include "Constructive.hpp"
#include "../Commons.hpp"
#include "../ProblemInstance.hpp"

#include <functional>

using namespace twtjssp;

/**
 * Class used to define a GRASP method, you can override his methods to create your own grasp
 */

class Grasp : public Constructive {

public:
    Grasp();
    Grasp(ProblemInstance instance, double _alpha = 0);

	virtual Solution apply();	/*!< applies the grasp method */
	virtual void print_graphic();
	virtual void print_method_informations();

protected:

	ScheduleMatrix jobs_temp; 	/*!< temporary variable */
	vector<int> restricts; 		/*!< restricts operations */
    double alpha;   			/*!< defines how greedy will be your grasp  */

	virtual float define_priority(Schedule op); /*!< method used to evaluate a schedule */
	virtual int choose_schedule();
    virtual float valor_grasp(float min, float max);  /*!< returns the value which defines the operation's restrict list */
	void remove_choosed_schedule(int index);


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