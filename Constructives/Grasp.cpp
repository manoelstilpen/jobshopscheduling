#include "Grasp.hpp"

Grasp::Grasp(){
	alpha = 0.3;
	this->repeat = 1;
}

Grasp::Grasp(ProblemInstance instance, double alpha){
	this->instance = instance;
	evaluator.set_instance(this->instance);
	this->jobs = instance.get_vec_schedules();
	this->alpha = alpha;
	this->repeat = 1;
}

Solution Grasp::apply_grasp1(){
	/*
	 * GRASP CONSTRUCTIVE
	 * GRASP MOD
	 */

	srand(time(NULL));
	media_atraso = 0;

	for(int l = 0 ; l<this->repeat ; l++){

		ScheduleMatrix jobs_temp = this->jobs;

		int nMachines = instance.get_num_machines();
		int nTasks = instance.get_num_tasks();
		int nJobs = instance.get_num_jobs();

		solution.clear();
		solution.resize(nMachines);

		for(int i=0 ; i<nJobs*nTasks ; i++){

			vector<Custo> custos;
			for(int j=0 ; j<jobs_temp.size() ; j++){
				 // Retorna o tempo de execucao caso o job fosse inserido, considerando tambem as prioridades
				//custos.push_back(Custo(jobs_temp[j][0].job, jobs_temp[j][0].task, j, analisa_manoel(jobs_temp[j][0])));
			}

			// Analise de qual é o menor custo
			float menor = INF;
			float maior = -INF;
			for(int j=0 ; j<custos.size() ; j++){
				if(custos[j].custo < menor){
					menor = custos[j].custo;
				}
				if(custos[j].custo > maior){
					maior = custos[j].custo;
				}
			}

			float limite_grasp = maior - this->alpha*(maior-menor);

			// Salva os indices dos jobs que tem os menores custos
			vector<int> tarefas_restritas;
			for(int j=0 ; j<custos.size() ; j++){
				if(custos[j].custo >= limite_grasp){
					tarefas_restritas.push_back(custos[j].indice);
				}
			}

/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////
			for(int j=0 ; j<jobs_temp.size() ; j++){														
				cout << "JOB " << j << ": ";
				for(int k=0 ; k<jobs_temp[j].size() ; k++){
					cout << "(" << jobs_temp[j][k].job << "," << jobs_temp[j][k].task << "," << jobs_temp[j][k].machine << "," << jobs_temp[j][k].time_execution << ") - ";
				}
				cout << endl;
			}
*/
			cout << "CUSTOS:";
			for(int j=0 ; j<custos.size() ; j++){
				cout << "(" << custos[j].job << "," << custos[j].task << "," << custos[j].indice << "," << custos[j].custo << ") - ";
			}
			cout << endl;
/*
			cout << "LISTA: ";
			for(int j=0 ; j<tarefas_restritas.size() ; j++){
				print_schedule(jobs_temp[tarefas_restritas[j]][0]);
			}
			cout << endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
*/			

			
			int rand_index = rand() % tarefas_restritas.size();
			solution = aloca_tarefa(&solution, &(this->jobs), jobs_temp[tarefas_restritas[rand_index]][0]);

			cout << "escolhido: ";
			print_schedule(jobs_temp[tarefas_restritas[rand_index]][0]);
			cout << endl << "=================" << endl << endl;

			// Remove a solucao ja alocada - remove a primeira posicao
			jobs_temp[tarefas_restritas[rand_index]].erase(jobs_temp[tarefas_restritas[rand_index]].begin());
			if(jobs_temp[tarefas_restritas[rand_index]].size() == 0){
				// Caso ja tenha alocado todas as tarefas do job, elimina o job da matriz
				jobs_temp.erase(jobs_temp.begin()+tarefas_restritas[rand_index]);
			}
		}

		// Acumula o atraso (quando é executado mais de uma vez)
		media_atraso += evaluator.evaluate_solution(solution);
	
	}

	// Calcula a media de atraso
	media_atraso = media_atraso / this->repeat;
	return solution;
}

Solution Grasp::apply_grasp2(){
	/*
	 * GRASP CONSTRUCTIVE
	 * Cria solucao considerando o custo das tarefas, dá-se prioridade as tarefas que podem ser inseridas imediatamente.
	 * Aloca aquela que possuir o menor custo na solucao apos ser inserida
	 * Em caso de empate de tarefas, opta-se por aquela que se inserida, deixa o menor tempo acumulado em sua maquina
	 */

	srand(time(NULL));
	media_atraso = 0;

	for(int l = 0 ; l<this->repeat ; l++){

		ScheduleMatrix jobs_temp = this->jobs;

		int nMachines = instance.get_num_machines();
		int nTasks = instance.get_num_tasks();
		int nJobs = instance.get_num_jobs();

		solution.clear();
		solution.resize(nMachines);

		for(int i=0 ; i<nJobs*nTasks ; i++){

			vector<Custo> custos;
			for(int j=0 ; j<jobs_temp.size() ; j++){
				 // Retorna o tempo de execucao caso o job fosse inserido, considerando tambem as prioridades
				custos.push_back(Custo(jobs_temp[j][0].job, jobs_temp[j][0].task, j, evaluator.analisa_job(jobs[j][0], solution, alpha)));
			}

			// Analise de qual é o menor custo
			int menor = INF;
			for(int j=0 ; j<custos.size() ; j++){
				if(custos[j].custo <= menor){
					menor = custos[j].custo;
				}
			}

			// Salva os indices dos jobs que tem os menores custos
			vector<int> tarefas_restritas;
			for(int j=0 ; j<custos.size() ; j++){
				if(custos[j].custo == menor){
					tarefas_restritas.push_back(custos[j].indice);
				}
			}

/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////
			for(int j=0 ; j<jobs_temp.size() ; j++){														
				cout << "JOB " << j << ": ";
				for(int k=0 ; k<jobs_temp[j].size() ; k++){
					cout << "(" << jobs_temp[j][k].job << "," << jobs_temp[j][k].task << "," << jobs_temp[j][k].machine << "," << jobs_temp[j][k].time_execution << ") - ";
				}
				cout << endl;
			}

			cout << "CUSTOS:";
			for(int j=0 ; j<custos.size() ; j++){
				cout << "(" << custos[j].job << "," << custos[j].task << "," << custos[j].indice << "," << custos[j].custo << ") - ";
			}
			cout << endl;

			cout << "LISTA: ";
			for(int j=0 ; j<tarefas_restritas.size() ; j++){
				print_schedule(jobs_temp[tarefas_restritas[j]][0]);
			}
			cout << endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
*/			
			menor = 0;

			// Caso tenha empate
			if(tarefas_restritas.size() > 1){
				/* 
				 * Se considerar o menor tempo de processamento como criterio de desempate,
				 * o atraso da solucao fica muito alto.
				 * A melhor opcao é considerar a tarefa que implica no menor tempo acumulado em sua maquina.
				 */

				vector<int> makespan;
				for(int j=0 ; j<tarefas_restritas.size() ; j++){
					// Retorna o tempo acumulado da maquina caso a tarefa fosse inserida
					makespan.push_back(evaluator.analisa_machine(jobs_temp[tarefas_restritas[j]][0], solution));
				}

				// Procura pelo menor
				for(int j=0 ; j<makespan.size() ; j++){
					if(makespan[j] < makespan[menor]){
						menor = j;
					}
				}

			}
/*
			cout << "escolhida: " << jobs_temp[tarefas_restritas[menor]][0].job << " " << jobs_temp[tarefas_restritas[menor]][0].task <<" " << jobs_temp[tarefas_restritas[menor]][0].machine <<" " << jobs_temp[tarefas_restritas[menor]][0].time_execution<< endl;
			print_partial();
			cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
*/
			solution = aloca_tarefa(&solution, &(this->jobs), jobs_temp[tarefas_restritas[menor]][0]);

			// Remove a solucao ja alocada - remove a primeira posicao
			jobs_temp[tarefas_restritas[menor]].erase(jobs_temp[tarefas_restritas[menor]].begin());
			if(jobs_temp[tarefas_restritas[menor]].size() == 0){
				// Caso ja tenha alocado todas as tarefas do job, elimina o job da matriz
				jobs_temp.erase(jobs_temp.begin()+tarefas_restritas[menor]);
			}
		}	

		media_atraso += evaluator.evaluate_solution(solution);

	}

	media_atraso = media_atraso / this->repeat;
	return solution;
}

Solution Grasp::grasp_SPRT(){
	/*
	 * GRASP CONSTRUCTIVE
	 * Cria solucao considerando o custo das tarefas.
	 * Aloca aquela que possuir o menor custo na solucao apos ser inserida
	 * Em caso de empate de tarefas, opta-se por aquela que se inserida, deixa o menor tempo acumulado em sua maquina
	 */

	srand(time(NULL));
	media_atraso = 0;

	for(int l = 0 ; l<this->repeat ; l++){

		ScheduleMatrix jobs_temp = this->jobs;

		int nMachines = instance.get_num_machines();
		int nTasks = instance.get_num_tasks();
		int nJobs = instance.get_num_jobs();

		solution.clear();
		solution.resize(nMachines);

		for(int i=0 ; i<nJobs*nTasks ; i++){

			vector<Custo> custos;
			for(int j=0 ; j<jobs_temp.size() ; j++){
				 // Retorna o tempo de execucao caso o job fosse inserido, considerando tambem as prioridades
				custos.push_back(Custo(jobs_temp[j][0].job, jobs_temp[j][0].task, j, analisa_prioridade(jobs_temp[j][0])));
			}

			// Analise de qual é o menor e maior custo
			float menor = INF;
			float maior = -INF;
			for(int j=0 ; j<custos.size() ; j++){
				if(custos[j].custo < menor){
					menor = custos[j].custo;
				}
				if(custos[j].custo > maior){
					maior = custos[j].custo;
				}
			}

			float limite_grasp = menor + this->alpha*(maior-menor);
			//cout << "Lim: " << limite_grasp << endl;

			// Salva os indices dos jobs que tem os menores custos
			vector<int> tarefas_restritas;
			for(int j=0 ; j<custos.size() ; j++){
				if(custos[j].custo <= limite_grasp){
					tarefas_restritas.push_back(custos[j].indice);
				}
			}

/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////
			for(int j=0 ; j<jobs_temp.size() ; j++){														
				cout << "JOB " << j << ": ";
				for(int k=0 ; k<jobs_temp[j].size() ; k++){
					cout << "(" << jobs_temp[j][k].job << "," << jobs_temp[j][k].task << "," << jobs_temp[j][k].machine << "," << jobs_temp[j][k].time_execution << ") - ";
				}
				cout << endl;
			}
*/
/*
			cout << "CUSTOS:";
			for(int j=0 ; j<custos.size() ; j++){
				cout << "(" << custos[j].job << "," << custos[j].task << "," << custos[j].indice << "," << custos[j].custo << ") - ";
			}
			cout << endl;

			cout << "RESTRITOS: ";
			for(int j=0 ; j<tarefas_restritas.size() ; j++){
				print_schedule(jobs_temp[tarefas_restritas[j]][0]);
			}
			cout << endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
*/		

/*
			cout << "escolhida: " << jobs_temp[tarefas_restritas[random_index]][0].job << " " << jobs_temp[tarefas_restritas[random_index]][0].task <<" " << jobs_temp[tarefas_restritas[random_index]][0].machine <<" " << jobs_temp[tarefas_restritas[random_index]][0].time_execution<< endl;
			print_partial();
			cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
*/

			if(tarefas_restritas.size() > 0){

				int random_index = rand() % tarefas_restritas.size();
				solution = aloca_tarefa(&solution, &(this->jobs), jobs_temp[tarefas_restritas[random_index]][0]);
				//cout << tarefas_restritas[random_index] << endl;

				// Remove a solucao ja alocada - remove a primeira posicao
				jobs_temp[tarefas_restritas[random_index]].erase(jobs_temp[tarefas_restritas[random_index]].begin());
				if(jobs_temp[tarefas_restritas[random_index]].size() == 0){
					// Caso ja tenha alocado todas as tarefas do job, elimina o job da matriz
					jobs_temp.erase(jobs_temp.begin()+tarefas_restritas[random_index]);
				}
			}
		}	

		media_atraso += evaluator.evaluate_solution(solution);

	}

	media_atraso = media_atraso / this->repeat;
	return solution;
}

float Grasp::analisa_prioridade(Schedule tarefa){
	// priority = s / RPT

	float s = this->instance.get_due_times()[tarefa.job];
	int size = solution[tarefa.machine].size();
	if(size > 0){
		s -= this->solution[tarefa.machine].back().time_execution;
	}

	float rpt = 0; // tempo de processamento restante 
	for(int i=tarefa.task ; i<jobs[tarefa.job].size() ; i++){
		rpt += jobs[tarefa.job][i].time_execution;
	}

	s -= rpt;
	//cout << "Job: " << tarefa.job << " " << tarefa.task << " " << s << " " << rpt << endl;
	return (float) s / rpt; 
}

float Grasp::analisa_mod(Schedule tarefa){
	// max (t+p(i,j), d(i,j))
	int mod;
	int quant_tarefas = solution[tarefa.machine].size();
	int processTime = this->jobs[tarefa.job][tarefa.task].time_execution;
	int due_date = this->instance.get_due_times()[tarefa.job];

	if(quant_tarefas == 0){
		mod = processTime;
	} else {
		mod = processTime + solution[tarefa.machine][quant_tarefas-1].time_execution;
	}

	if(due_date > mod){
		mod = due_date;
	}

	return mod;

}

void Grasp::set_instance(ProblemInstance p){
	this->instance = p;
	this->jobs = this->instance.get_vec_schedules();
}

void Grasp::set_alpha(double a){
	this->alpha = a;
}

void Grasp::set_repeat(int r){
	this->repeat = r;
}

int Grasp::get_atraso(){
	return this->media_atraso;
}

void Grasp::print(){
	for(int i=0 ; i<solution.size() ; i++){
		cout << "MACHINE " << i << ": ";
		for(int j=0 ; j<solution[i].size() ; j++){
			cout << "(" << solution[i][j].job << "," << solution[i][j].task << "," << solution[i][j].time_execution << ") - ";
		}
		cout << endl;
	}

	evaluator.print();
}

void Grasp::print_partial(){
	for(int i=0 ; i<solution.size() ; i++){
		cout << "MACHINE " << i << ": ";
		for(int j=0 ; j<solution[i].size() ; j++){
			cout << "(" << solution[i][j].job << "," << solution[i][j].task << "," << solution[i][j].time_execution << ") - ";
		}
		cout << endl;
	}
}

void Grasp::print_graph(){
	cout << this->alpha << "\t" << this->media_atraso << endl;
}