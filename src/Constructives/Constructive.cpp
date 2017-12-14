#include "Constructive.hpp"

Constructive::Constructive(){

}

Constructive::Constructive(ProblemInstance p, double _alpha) : solution(p), evaluator(p), alpha(_alpha) {
    this->repeat = 1;
    this->instance = p;
    this->nMachines = p.get_num_machines();
    this->nJobs = p.get_num_jobs();
    this->nOperations = p.get_num_tasks();
}

Solution Constructive::apply(){

    //	print_method_informations();

    ScheduleMatrix jobs_temp;

    this->media_atraso = 0;

    for(int l = 0 ; l<repeat ; l++){
        
        // realiza copia para ser possivel remover schedules
        jobs_temp = instance.get_vec_schedules();

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

            // Analise de qual é a menor e maior prioridade
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
            int index = choose_schedule(jobs_temp, restricts);

            solution.aloca_tarefa(jobs_temp[restricts[index]][0]);
            remove_choosed_schedule(jobs_temp, restricts[index]);
        }

        // Acumula o atraso (util quando repeat > 1)
        int atraso = evaluator.evaluate_solution(solution);
        this->media_atraso += atraso;
    }

    // Calcula a media de atraso
    this->media_atraso /= this->repeat;
    return solution;

}

void Constructive::remove_choosed_schedule(ScheduleMatrix& jobs_temp, int jobId){

	// Remove a solucao ja alocada - remove a primeira posicao
	jobs_temp[jobId].erase(jobs_temp[jobId].begin());
	if(jobs_temp[jobId].size() == 0){
		// Caso ja tenha alocado todas as tarefas do job, elimina o job da matriz
		jobs_temp.erase(jobs_temp.begin()+jobId);
	}
}

float Constructive::valor_grasp(float min, float max){
	// 0 -> Greedy
	// 1 -> Random
    return (float) (min + alpha*(max-min));
}

void Constructive::print(){
    for(int i=0 ; i<solution.size() ; i++){
        cout << "MACHINE " << i << ": ";
        for(int j=0 ; j<solution[i].size() ; j++){
            cout << "(" << solution[i][j].job << "," << solution[i][j].task << "," << solution[i][j].time_execution << ") - ";
        }
        cout << endl;
    }

    evaluator.print();
}

void Constructive::print_graphic(){
    cout << this->media_atraso << endl;
}

void Constructive::set_repeat(int t){ 
    this->repeat = t;
}

void Constructive::set_instance(ProblemInstance p) {
    this->instance = p;
}

int Constructive::get_atraso(){ 
    return this->media_atraso;
}
