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

	vector<int> teste(10);
	fill(teste.begin(), teste.end(),0);

	for(int i=0 ; i<nJobs*nTasks ; i++){

		int max = -INF;
		int min = INF;
		//procura pelo maior e menor tempo
		for(int j=0 ; j<jobs.size() ; j++){
			if(jobs[j][0].time_execution > max){
				max = jobs[j][0].time_execution;
			}
			if(jobs[j][0].time_execution < min){
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
/*
		cout << "LISTA: ";
		for(int j=0 ; j<tarefas_restritas.size() ; j++){
			cout << "(" << jobs[tarefas_restritas[j]][0].machine << " " << jobs[tarefas_restritas[j]][0].time_execution << ") - ";
		}
		cout << limite_grasp << endl;
*/

		if(tarefas_restritas.size() > 0){
			int random_index = rand() % tarefas_restritas.size();
			Schedule tarefa_escolhida = jobs[tarefas_restritas[random_index]][0];
			// aloca a tarefa na solucao
			JobTask aux(tarefa_escolhida.job,tarefa_escolhida.task);
			//cout << "escolhido: " << jobs[tarefas_restritas[random_index]][0].machine << " " << jobs[tarefas_restritas[random_index]][0].time_execution << endl;
			solution[tarefa_escolhida.machine].push_back(aux);

			//remove a solucao ja alocada - remove a primeira posicao
			jobs[tarefas_restritas[random_index]].erase(jobs[tarefas_restritas[random_index]].begin());
			if(jobs[tarefas_restritas[random_index]].size() == 0){
				// caso tenha alocado todas as tarefas do job, elimina-o da matriz
				jobs.erase(jobs.begin()+tarefas_restritas[random_index]);
			}
			teste[tarefa_escolhida.machine]++;
		}

	}

	for(int i=0 ; i<10 ; i++){
		cout << teste[i] << " ";
	}
	cout << endl;

	//printSolution(10,10,solution);

	for(int i=0 ; i<nMachines ; i++){
		cout << "MACHINE " << i << ": ";
		for(int j=0 ; j<nTasks ; j++){
			cout << "(" << solution[i][j].job << "," << solution[i][j].task << "," << instance.get_vec_schedules()[solution[i][j].job][solution[i][j].task].time_execution << ") - ";
		}
		cout << endl;
	}

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