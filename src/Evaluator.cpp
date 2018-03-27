#include "Evaluator.hpp"

Evaluator::Evaluator(){
	this->total_atraso = 0;
}

int Evaluator::evaluate_solution(Solution solution){
	// data de conclusão é quando terminou
	// data de entrega é fornecido pela instancia

	//int nMachines = this->instance.get_num_machines();
	int nJobs = ProblemInstance::getNumJobs();
	int nOperations = ProblemInstance::getNumOperations();
	ScheduleMatrix jobs = ProblemInstance::getVecSchedules();
	expectedTimes = ProblemInstance::getDueTimes();
	vector<int> priorities = ProblemInstance::getVecPriorities();

	realTimes.resize((ulong)nJobs);
	vector<int> tardiness((ulong)nJobs);

	total_atraso = 0;

	for(int i=0 ; i<nJobs ; i++){
		int lastMachine = jobs[i][nOperations-1].machine;
		for(int j=nJobs-1 ; j>=0 ; j--){
			if(solution[lastMachine][j].job == i){
				realTimes[i] = (solution[lastMachine][j].time_execution);
				tardiness[i] = (realTimes[i] - expectedTimes[i]) * ProblemInstance::getPriorityFromJob(i);
				if(tardiness[i] < 0){
					tardiness[i] = 0;
				}
				total_atraso += (tardiness[i]);
				break;
			}
		}
	}

	testa_solucao(solution);

	return total_atraso;
}

int Evaluator::evaluate_by_graph(Graph _graph){

	int soma_atraso = 0;
	int v_per_job = _graph.getVertexPerJob();
	_graph.getCriticalPath();
	
	for(int i=1 ; i<=ProblemInstance::getNumJobs() ; i++){
		soma_atraso += ((_graph.getDistanceFrom(v_per_job*i) * ProblemInstance::getPriorityFromJob(i-1)));
	}

	return soma_atraso;
}

int Evaluator::evaluate_by_graph(Solution _s){
 	return evaluate_by_graph(_s.getGraph());
}

bool Evaluator::testa_solucao(Solution solution){
	ScheduleMatrix jobs = ProblemInstance::getVecSchedules();

	for(unsigned int i=0 ; i<jobs.size() ; i++){
		int timeAtual = 0;
		int timeLast = 0;

		for(unsigned int j=0 ; j<jobs[i].size() ; j++){
			int machine = jobs[i][j].machine;
			timeAtual = 0;

			for(unsigned int k=0 ; k<solution[machine].size() ; k++){

				if((unsigned)solution[machine][k].job == i){
					int tempoInicio = solution[machine][k].time_execution - jobs[i][j].time_execution;

					if(tempoInicio < timeLast || tempoInicio < timeAtual){
						cout << "ERRO NA SOLUCAO!!!" << endl;
						cout << i << " " << j << endl;
						return false;
					}
					timeLast = solution[machine][k].time_execution;
					break;
				}
				timeAtual = solution[machine][k].time_execution;
			}
		}
	}

	return true;
}

void Evaluator::print(){
	for(int i=0 ; i<ProblemInstance::getNumJobs() ; i++){
		cout << "(" << realTimes[i] << "," << expectedTimes[i] << ") - ";
	}
	cout << endl << "TOTAL: " << total_atraso << endl;
}
