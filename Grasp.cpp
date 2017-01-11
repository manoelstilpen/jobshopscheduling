#include "Grasp.hpp"

Grasp::Grasp(){
	alpha = 0.3;
}

Grasp::Grasp(ProblemInstance instance, double alpha){
	this->instance = instance;
	this->alpha = alpha;
}

Solution Grasp::apply_grasp(){
	// primeiro criar lista de tarefas elegiveis
	// depois selecionar lista de tarefas restritas

	srand(time(NULL));

	int nMachines = instance.get_num_machines();
	int nTasks = instance.get_num_tasks();
	int nJobs = instance.get_num_jobs();
	ScheduleMatrix jobs = instance.get_vec_schedules();

	Solution solution;
	solution.resize(nMachines);
/*	for(int i=0 ; i<nMachines ; i++){
		for(int j=0 ; j<nJobs ; j++){
			solution[i].resize(nTasks);
		}
	}
*/
	for(int i=0 ; i<nJobs*nTasks ; i++){

		int max = -INF;
		int min = INF;
		//procura pelo maior e menor tempo
		for(int j=0 ; j<jobs.size() ; j++){
			if(jobs[j][0].time_execution > max){
				max = jobs[j][0].time_execution;
			} else if(jobs[j][0].time_execution < min){
				min = jobs[j][0].time_execution;
			}
		}

		int limite_grasp = max - alpha*(max-min);

		// armazena os indices
		vector<int> tarefas_restritas;
		for(int j=0 ; j<jobs.size() ; j++){
			// se o tempo for maior que o criterio grasp, entao, salva seu indice
			if(jobs[j][0].time_execution >= limite_grasp){
				tarefas_restritas.push_back(j);
			}
		}

		if(tarefas_restritas.size() > 0){
			int random_index = rand() % tarefas_restritas.size();
			Schedule tarefa_escolhida = jobs[random_index][0];
			// aloca a tarefa na solucao
			JobTask aux(tarefa_escolhida.job,tarefa_escolhida.task);
			solution[tarefa_escolhida.machine].push_back(aux);
			//remove a solucao ja alocada - remove a primeira posicao
			jobs[random_index].erase(jobs[random_index].begin());
		}

	}

	printSolution(10,10,solution);

	return solution;
}

void Grasp::set_instance(ProblemInstance p){
	this->instance = p;
}

void Grasp::set_alpha(double a){
	this->alpha = a;
}

void Grasp::set_repeat(int r){
	this->repeat = r;
}