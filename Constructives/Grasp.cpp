#include "Grasp.hpp"

Grasp::Grasp() : Constructive(){

}

Grasp::Grasp(ProblemInstance instance, double _alpha) : 
    Constructive(instance),
    alpha(_alpha){

}

Solution Grasp::apply(){
    /*
	 * GRASP CONSTRUCTIVE
	 * GRASP MOD 
	 */

	srand(time(NULL));
	this->media_atraso = 0;

	for(int l = 0 ; l<this->repeat ; l++){

        // realiza copia para ser possivel remover scheduless
        ScheduleMatrix jobs_temp = this->instance.get_vec_schedules();

		solution.clear();
		solution.resize(nMachines);

		for(int i=0 ; i<this->nJobs*this->nOperations ; i++){

			vector<Custo> custos;
			for(int j=0 ; j<jobs_temp.size() ; j++){
				 // avalia a prioridade daquela operacao
				custos.push_back(Custo
                    (jobs_temp[j][0].job, jobs_temp[j][0].task, j, define_priority(jobs_temp[j][0])));
			}

			// Analise de qual é o menor custo do grasp
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

			float limite_grasp = valor_grasp(menor, maior);

			// Salva os indices dos jobs que tem os menores custos
			vector<int> tarefas_restritas;
			for(int j=0 ; j<custos.size() ; j++){
				if(custos[j].custo <= limite_grasp){
					tarefas_restritas.push_back(custos[j].indice);
				}
			}		

            // escolhe aleatoriamente um indice
			int rand_index = rand() % tarefas_restritas.size();
            // aloca a tarefa escolhida aleatoriamente
			solution.aloca_tarefa(jobs_temp[tarefas_restritas[rand_index]][0]);

			// Remove a solucao ja alocada - remove a primeira posicao
			jobs_temp[tarefas_restritas[rand_index]].erase(jobs_temp[tarefas_restritas[rand_index]].begin());
			if(jobs_temp[tarefas_restritas[rand_index]].size() == 0){
				// Caso ja tenha alocado todas as tarefas do job, elimina o job da matriz
				jobs_temp.erase(jobs_temp.begin()+tarefas_restritas[rand_index]);
			}
		}

		// Acumula o atraso (quando é executado mais de uma vez)
		this->media_atraso += evaluator.evaluate_solution(solution);
	}

	// Calcula a media de atraso
	this->media_atraso /= this->repeat;
	return solution;
}

float Grasp::define_priority(Schedule op){
    // max (t+p(i,j), d(i,j))
	int mod;
	int quant_tarefas = solution[op.machine].size();
	int processTime = this->instance[op.job][op.task].time_execution;
	int due_date = this->instance.get_due_times()[op.job];

	if(quant_tarefas == 0){
		mod = processTime;
	} else {
		mod = processTime + solution[op.machine][quant_tarefas-1].time_execution;
	}

	if(due_date > mod){
		mod = due_date;
	}

	return mod;
}

float Grasp::valor_grasp(int min, int max){
    return (max - this->alpha*(max-min));
}