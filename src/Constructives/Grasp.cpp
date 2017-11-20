#include "Grasp.hpp"

Grasp::Grasp() : Constructive(){
}

Grasp::Grasp(ProblemInstance instance, double _alpha) : 
    Constructive(instance),
    alpha(_alpha) {

}

void Grasp::print_method_informations(){
	cout << "=========================================================================================" << endl;
	cout << " -> CONSTRUCTIVE GRASP MOD <- " << endl;
	cout << "ALPHA: " << this->alpha << endl;
}

Solution Grasp::apply(){
    /*
	 * GRASP CONSTRUCTIVE
	 * GRASP MOD 
	 */

//	print_method_informations();

	this->media_atraso = 0;

	srand(time(0));	

	for(int l = 0 ; l<this->repeat ; l++){
		
        // realiza copia para ser possivel remover schedules
        jobs_temp = this->instance.get_vec_schedules();

		solution.clear();
		solution.resize(nMachines);

		for(int i=0 ; i<nJobs*nOperations ; i++){

			vector<Custo> custos;
			for(int j=0 ; j<jobs_temp.size() ; j++){
				 // avalia a prioridade das operacoes candidatas
				custos.push_back(
					Custo(jobs_temp[j][0].job, jobs_temp[j][0].operation, j, define_priority(jobs_temp[j][0]))
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
	//			cout << custos[j].job << "-" << custos[j].task << " " << custos[j].custo << endl;
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
	//		cout << "escolhido: " << jobs_temp[restricts[index]][0].job << "-" << jobs_temp[restricts[index]][0].task << endl;
			solution.aloca_tarefa(jobs_temp[restricts[index]][0]);
			remove_choosed_schedule(index);
			
		}

		// Acumula o atraso (util quando repeat > 1)
		this->media_atraso += evaluator.evaluate_solution(solution);
	}

	// Calcula a media de atraso
	this->media_atraso /= this->repeat;
	return solution;
}

Solution Grasp::refinement(Solution s){
	local_search = new FirstImprovement(s);
	solution = local_search->apply();

	return solution;
}

int Grasp::choose_schedule(){
	int menor = 0;
    if(restricts.size() > 1){
        /* 
         * Se considerar o menor tempo de processamento como criterio de desempate,
         * o atraso da solucao fica muito alto.
         * A melhor opcao é considerar a tarefa que implica no menor tempo acumulado em sua maquina.
         */

        vector<int> acumulatedTimes;
        for(int j=0 ; j<restricts.size() ; j++){
            // Retorna o tempo acumulado da maquina caso a tarefa fosse inserida
			int tempoAcumulado = solution.time_can_be_alocated(jobs_temp[restricts[j]][0]) + jobs_temp[restricts[j]][0].time_execution;
            acumulatedTimes.push_back(tempoAcumulado);
        }

        // Procura pelo menor
        for(int j=0 ; j<acumulatedTimes.size() ; j++){
            if(acumulatedTimes[j] < acumulatedTimes[menor]){
                menor = j;
            }
        }

    }
    
    return menor;	
}

float Grasp::define_priority(Schedule op){
	 /* Retorna o tempo de folga ou atraso da operacao */

	// tempo de conclusao da operacao caso fosse inserida
	int remainingTime = solution.time_can_be_alocated(op) + op.time_execution;
	
	// subtrai da data de entrega do job
	remainingTime -= instance.get_due_times()[op.job];
	
	// caso seja menor do que 0, significa que nao há atraso no job ate o momento
	if(remainingTime < 0) remainingTime = 0;

	return remainingTime;
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