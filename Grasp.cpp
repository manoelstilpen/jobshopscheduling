#include "Grasp.hpp"

Grasp::Grasp(){
	alpha = 0.3;
	this->repeat = 1;
}

Grasp::Grasp(ProblemInstance instance, double alpha){
	this->instance = instance;
	this->jobs = instance.get_vec_schedules();
	this->alpha = alpha;
	this->repeat = 1;
}

Solution Grasp::apply_grasp(){
	// primeiro criar lista de tarefas elegiveis
	// depois selecionar lista de tarefas restritas
	Solution solution;
	srand(time(NULL));
	int media_atraso = 0;

	for(int l = 0 ; l<this->repeat ; l++){

		ScheduleMatrix jobs = this->jobs;

		int nMachines = instance.get_num_machines();
		int nTasks = instance.get_num_tasks();
		int nJobs = instance.get_num_jobs();

		solution.clear();
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
				//cout << "escolhido: " << jobs[tarefas_restritas[random_index]][0].job << " " << jobs[tarefas_restritas[random_index]][0].task << endl;
				solution = alocaTarefa(&solution, tarefa_escolhida);

				//remove a solucao ja alocada - remove a primeira posicao
				jobs[tarefas_restritas[random_index]].erase(jobs[tarefas_restritas[random_index]].begin());
				if(jobs[tarefas_restritas[random_index]].size() == 0){
					// caso tenha alocado todas as tarefas do job, elimina-o da matriz
					jobs.erase(jobs.begin()+tarefas_restritas[random_index]);
				}
				teste[tarefa_escolhida.machine]++;
			}

		}

		Evaluator evaluator(solution, instance);
		media_atraso += evaluator.evaluateSolution();

	/*
		for(int i=0 ; i<10 ; i++){
			cout << teste[i] << " ";
		}
		cout << endl;
	*/
		//printSolution(10,10,solution);
	/*
		for(int i=0 ; i<nMachines ; i++){
			cout << "MACHINE " << i << ": ";
			for(int j=0 ; j<nTasks ; j++){
				cout << "(" << solution[i][j].job << "," << solution[i][j].task << "," << solution[i][j].time_execution << ") - ";
			}
			cout << endl;
		}
	*/
	}

	media_atraso = media_atraso / this->repeat;
	cout << this->alpha << "\t" << media_atraso << endl;

	return solution;
}

Solution Grasp::alocaTarefa(Solution* solution, Schedule tarefa){
	int machine = tarefa.machine;
	int nTasks = instance.get_num_tasks();
	int sizeMachine = (*solution)[machine].size(); // quantidade de tasks alocadas na maquina

	if(tarefa.task == 0){
		// se for a primeira tarefa do job, nao e necessario analisar se viola alguma regra
		if((*solution)[machine].size() == 0){
			// como nao tem outra tarefa alocada nessa maquina, apenas insere
			(*solution)[machine].push_back(tarefa);
		} else {
			int tempo = (*solution)[machine][sizeMachine-1].time_execution; // armazena o tempo acumulado
			tarefa.time_execution += tempo; // adiciona o tempo acumulado
			(*solution)[machine].push_back(tarefa);
		}

	} else {

		int lastMachine = jobs[tarefa.job][tarefa.task-1].machine;
		int timeLastTask = 0;
		// procura pelo instante que a ultima task DO JOB foi finalizada
		for(int i=0 ; i<(*solution)[lastMachine].size() ; i++){
			if((*solution)[lastMachine][i].job == tarefa.job){
				timeLastTask = (*solution)[lastMachine][i].time_execution;
				break;
			}
		}

		// tempo acumulado que a ultima tarefa DA MAQUINA foi executada
		int timeMachine = 0;
		if(sizeMachine != 0){
			timeMachine = (*solution)[machine][sizeMachine-1].time_execution;
		}
		
		if(timeMachine >= timeLastTask){
			tarefa.time_execution += (*solution)[machine][sizeMachine-1].time_execution;
			(*solution)[machine].push_back(tarefa);
		} else {
			tarefa.time_execution += timeLastTask;
			(*solution)[machine].push_back(tarefa);
		}

	}
	
	return *solution;
        
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