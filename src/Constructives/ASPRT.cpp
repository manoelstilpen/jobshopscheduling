#include "ASPRT.hpp"

ASPRT::ASPRT(double _alpha) : Constructive(_alpha) {

}

void ASPRT::print_method_informations(){
	cout << "=========================================================================================" << endl;
	cout << " -> CONSTRUCTIVE ASPRT <-" << endl;
	cout << "ALPHA: " << this->alpha << endl;
}

float ASPRT::define_priority(Schedule op){
    // Retorna o tempo de folga ou atraso da operacao

	// tempo de conclusao da operacao caso fosse inserida
	int remainingTime = solution.time_can_be_alocated(op) + op.time_execution;
	
	// subtrai da data de entrega do job
	remainingTime -= ProblemInstance::getDueTimeFromJob(op.job);
	
	// caso seja menor do que 0, significa que nao há atraso no job ate o momento
	if(remainingTime < 0) remainingTime = 0; 

	return remainingTime;
}

int ASPRT::choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts){
    return rand() % restricts.size(); 
}