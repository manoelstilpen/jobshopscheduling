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
        jobs_temp = this->instance.get_vec_schedules();

		solution.clear();
		solution.resize(nMachines);

		for(int i=0 ; i<nJobs*nOperations ; i++){

			vector<Custo> custos;
			for(int j=0 ; j<jobs_temp.size() ; j++){
				 // avalia a prioridade das operacoes candidatas
				custos.push_back(
					Custo(jobs_temp[j][0].job, jobs_temp[j][0].task, j, define_priority(jobs_temp[j][0]))
				);
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

			restricts.clear();
			for(int j=0 ; j<custos.size() ; j++){
				if(custos[j].custo <= limite_grasp){
					restricts.push_back(custos[j].indice);
				}
			}		
			
			// escolhe a operacao(retornando o indice), aloca na solucao e remove do vetor 
			int index = choose_schedule();
			solution.aloca_tarefa(jobs_temp[restricts[index]][0]);
			remove_choosed_schedule(index);
			
		}

		// Acumula o atraso (quando é executado mais de uma vez)
		this->media_atraso += evaluator.evaluate_solution(solution);
	}

	// Calcula a media de atraso
	this->media_atraso /= this->repeat;
	return solution;
}

int Grasp::choose_schedule(){
	// escolhe aleatoriamente um indice e retorna
	return rand() % restricts.size();
}

float Grasp::define_priority(Schedule op){
	// defines the function for mod rule

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

void Grasp::remove_choosed_schedule(int index){

	// Remove a solucao ja alocada - remove a primeira posicao
	jobs_temp[restricts[index]].erase(jobs_temp[restricts[index]].begin());
	if(jobs_temp[restricts[index]].size() == 0){
		// Caso ja tenha alocado todas as tarefas do job, elimina o job da matriz
		jobs_temp.erase(jobs_temp.begin()+restricts[index]);
	}
}

float Grasp::valor_grasp(float min, float max){
	// 0 -> Greedy
	// 1 -> Random
    return (float) (min + this->alpha*(max-min));
}

void Grasp::print_graphic(){
	cout << alpha << " " << media_atraso << endl;
}