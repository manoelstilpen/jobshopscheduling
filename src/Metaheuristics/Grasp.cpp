#include "Grasp.hpp"

Grasp::Grasp() : Constructive(){
}

Grasp::Grasp(ProblemInstance instance, double _alpha, bool _refine) : 
    alpha(_alpha), refine(_refine) {

}

void Grasp::print_method_informations(){
	cout << "=========================================================================================" << endl;
	cout << " -> GRASP <- " << endl;
	cout << "ALPHA: " << this->alpha << endl;
}

Solution Grasp::apply(){

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

			// Analise de qual é o menor e maior prioridade
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

		if(refine)
			solution = refinement(solution);

		// Acumula o atraso (util quando repeat > 1)
		int atraso = evaluator.evaluate_solution(solution);
		this->media_atraso += atraso;
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