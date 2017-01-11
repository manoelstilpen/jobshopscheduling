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

	ScheduleMatrix jobs = this->instance.get_vec_schedules();
	vector<int> expectedTimes = this->instance.get_vec_conclusion_times();
	vector<int> priorities = this->instance.get_vec_priorities();
	vector<int> realTimes(nJobs);

	for(int i=0 ; i<nJobs ; i++){
		int lastMachine = jobs[i][nTasks-1].machine;
		for(int j=0 ; j<nTasks ; j++){
			if(solution[lastMachine][j].job == i){
				realTimes[i] = solution[lastMachine][j].time_execution - expectedTimes[i];
				break;
			}
		}
	}
	
	int aux=0;
	for(int i=0 ; i<nJobs ; i++){
	//	cout << "(" << realTimes[i]-expectedTimes[i] << "," << expectedTimes[i] << ") - ";
		aux += (realTimes[i]-expectedTimes[i]);
	}
	cout << "TOTAL: " << aux << endl;
}

void Evaluator::set_instance(ProblemInstance p){
	this->instance = p;
}

void Evaluator::set_solution(Solution s){
	this->solution = s;
}