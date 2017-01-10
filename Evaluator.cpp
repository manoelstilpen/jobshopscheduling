#include "Evaluator.hpp"

Evaluator::Evaluator(){

}

Evaluator::Evaluator(Solution s, ProblemInstance p){
	this->solution = s;
	this->instance = p;
}

void Evaluator::evaluateSolution(){
	// data de conclusão é quando terminou
	// data de entrega é fornecido pela instancia
	int nMachines = this->instance.get_num_machines();
	int nJobs = this->instance.get_num_jobs();
	int nTasks = this->instance.get_num_tasks();

	vector<int> expectedTimes = this->instance.get_vec_conclusion_times();
	vector<int> realTimes(nJobs);
	ScheduleMatrix jobs = this->instance.get_vec_schedules();

	for(int i=0 ; i<nJobs ; i++){
		int delay = 0;
		for(int j=0 ; j<nMachines ; j++){
			for(int k=0 ; k<nJobs ; k++){
				int job = solution[j][k].job;
				int task = solution[j][k].task;
				delay += jobs[job][task].time_execution;
				if(this->solution[j][k].job == i){
					realTimes[i] = delay;
					break;
				}
			}
		}
	}

	int aux=0;
	for(int i=0 ; i<nJobs ; i++){
		cout << "(" << realTimes[i] << "," << expectedTimes[i] << ") - ";
		aux += realTimes[i];
	}
	cout << endl << "TOTAL: " << aux << endl;
}

void Evaluator::set_instance(ProblemInstance p){
	this->instance = p;
}

void Evaluator::set_solution(Solution s){
	this->solution = s;
}