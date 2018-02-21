#include "SPRT.hpp"

SPRT::SPRT(){

}

SPRT::SPRT(ProblemInstance p, double _alpha) : Constructive(p, _alpha) {

}

void SPRT::print_method_informations(){
    cout << "=========================================================================================" << endl;
	cout << " -> CONSTRUCTIVE SPRT <-" << endl;
    cout << "ALPHA: " << this->alpha << endl;
}


float SPRT::define_priority(Schedule op){
    // priority = s / RPT
	float s = instance.get_due_times()[op.job];
	//s -= (solution.time_can_be_alocated(op));
	s -= solution.makespan();

	float rpt = 0; // tempo de processamento restante 
	for(unsigned int i=op.operation ; i<instance[op.job].size() ; i++){
		rpt += (instance[op.job][i].time_execution);
	}

	s -= rpt;

    return (float) (s / rpt); 
}

int SPRT::choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts){
    return rand() % restricts.size();
}