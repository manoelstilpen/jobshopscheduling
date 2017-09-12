#include "Evaluator.hpp"

Evaluator::Evaluator(){
	this->total_atraso = 0;
}

Evaluator::Evaluator(ProblemInstance p){
	this->instance = p;
	this->total_atraso = 0;
}

int Evaluator::evaluate_solution(Solution solution){
	// data de conclusão é quando terminou
	// data de entrega é fornecido pela instancia

	this->solution = solution;
	int nMachines = this->instance.get_num_machines();
	int nJobs = this->instance.get_num_jobs();
	int nTasks = this->instance.get_num_tasks();
	ScheduleMatrix jobs = this->instance.get_vec_schedules();
	expectedTimes = this->instance.get_due_times();
	vector<int> priorities = this->instance.get_vec_priorities();

	realTimes.resize(nJobs);
	vector<int> tardiness(nJobs);

	total_atraso = 0;

	for(int i=0 ; i<nJobs ; i++){
		int lastMachine = jobs[i][nTasks-1].machine;
		for(int j=nJobs-1 ; j>=0 ; j--){
			if(solution[lastMachine][j].job == i){
				realTimes[i] = (solution[lastMachine][j].time_execution);
				tardiness[i] = (realTimes[i] - expectedTimes[i]) * instance.get_vec_priorities()[i];
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

int Evaluator::evaluate_by_graph(Graph graph){

	int soma_atraso = 0;
	int v_per_job = graph.getVertexPerJob();
	graph.bellmanFord();
	
	for(int i=1 ; i<=instance.get_num_jobs() ; i++){
		soma_atraso += (graph.getDistances()[v_per_job*i] * instance.get_vec_priorities()[i-1]);
	}

	return soma_atraso;
}

int Evaluator::evaluate_by_graph(Solution s){
	Graph graph = s.getGraph();

	int soma_atraso = 0;
	int v_per_job = graph.getVertexPerJob();
	
	graph.bellmanFord();
	
	for(int i=1 ; i<=instance.get_num_jobs() ; i++){
		soma_atraso += (graph.getDistances()[v_per_job*i] * instance.get_vec_priorities()[i-1]);
	}

	return soma_atraso;
}

bool Evaluator::testa_solucao(Solution solution){
	ScheduleMatrix jobs = instance.get_vec_schedules();

	for(int i=0 ; i<jobs.size() ; i++){
		int timeAtual = 0;
		int timeLast = 0;

		for(int j=0 ; j<jobs[i].size() ; j++){
			int machine = jobs[i][j].machine;
			timeAtual = 0;

			for(int k=0 ; k<solution[machine].size() ; k++){

				if(solution[machine][k].job == i){
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

void Evaluator::set_instance(ProblemInstance p){
	this->instance = p;
}

void Evaluator::set_solution(Solution s){
	this->solution = s;
}

void Evaluator::print(){
	for(int i=0 ; i<instance.get_num_jobs() ; i++){
		cout << "(" << realTimes[i] << "," << expectedTimes[i] << ") - ";
	}
	cout << endl << "TOTAL: " << total_atraso << endl;
}
