#include "Evaluator.hpp"

Evaluator::Evaluator(){

}

Evaluator::Evaluator(Solution s, ProblemInstance p){
	this->solution = s;
	this->instance = p;
}

int Evaluator::evaluateSolution(){
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
				realTimes[i] = (solution[lastMachine][j].time_execution - expectedTimes[i])*priorities[i];
				break;
			}
		}
	}
	
	int aux=0;
	for(int i=0 ; i<nJobs ; i++){
		cout << "(" << realTimes[i]-expectedTimes[i] << "," << expectedTimes[i] << ") - ";
		aux += (realTimes[i]-expectedTimes[i]);
	}
	cout << endl << "TOTAL: " << aux << endl;

	testa_solucao(solution);

	return aux;
}

bool Evaluator::testa_solucao(Solution solution){
	int nJobs = instance.get_num_jobs();
	int nTasks = instance.get_num_tasks();
	int nMachines = instance.get_num_machines();
	ScheduleMatrix jobs = instance.get_vec_schedules();

	for(int i=0 ; i<nJobs ; i++){
		int timeAtual = 0;
		int timeLast = 0;
		for(int j=0 ; j<nTasks ; j++){
			int machine = jobs[i][j].machine;
			timeAtual = 0;
			for(int k=0 ; k<nTasks ; k++){
				if(solution[machine][k].job == i){
					if(timeAtual < timeLast){
						cout << "ERRO NA SOLUCAO" << endl;
						timeLast = timeAtual;
						break;
					}
				}
				timeAtual += solution[machine][k].time_execution;
			}
		}
	}
}

void Evaluator::set_instance(ProblemInstance p){
	this->instance = p;
}

void Evaluator::set_solution(Solution s){
	this->solution = s;
}