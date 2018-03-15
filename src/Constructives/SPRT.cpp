#include "SPRT.hpp"

SPRT::SPRT(double _alpha) : Constructive(_alpha) {

}

void SPRT::print_method_informations(){
    cout << "=========================================================================================" << endl;
	cout << " -> CONSTRUCTIVE SPRT <-" << endl;
    cout << "ALPHA: " << this->alpha << endl;
}


float SPRT::define_priority(Schedule op){
    // priority = s / RPT
	float s = ProblemInstance::getDueTimeFromJob(op.job);
	//s -= (solution.time_can_be_alocated(op));
	s -= solution.makespan();

	float rpt = 0; // tempo de processamento restante
	for(int i=op.operation ; i<ProblemInstance::getOperationsFromJob(op.job).size() ; i++){
		rpt += ProblemInstance::getSchedule(op.job, i).time_execution;
	}

	s -= rpt;

    return (float) (s / rpt); 
}

int SPRT::choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts){
    return rand() % restricts.size();
}