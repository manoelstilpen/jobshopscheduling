#include "Constructive.hpp"

Constructive::Constructive(){
    repeat = 1;
}

Constructive::Constructive(double _alpha) : alpha(_alpha) {
    this->repeat = 1;
    this->nMachines = ProblemInstance::getNumMachines();
    this->nJobs = ProblemInstance::getNumJobs();
    this->nOperations = ProblemInstance::getNumOperations();
}

Solution Constructive::apply(){

//    print_method_informations();

    ScheduleMatrix jobs_temp;

    this->media_atraso = 0;

    for(int l = 0 ; l<repeat ; l++){
        
        // realiza copia para ser possivel remover schedules
        jobs_temp = ProblemInstance::getVecSchedules();

        solution.clear();
        solution.resize(nMachines);

        for(int i=0 ; i<nJobs*nOperations ; i++){

            vector<Custo> custos;
            for(unsigned int j=0 ; j<jobs_temp.size() ; j++){
                // avalia a prioridade das operacoes candidatas
                custos.push_back(
                    Custo(j, define_priority(jobs_temp[j][0]))
                );
            }

            // ordena para extrair qual é a menor e a maior prioridade
            std::sort(custos.begin(), custos.end(), [&](const Custo& a, const Custo& b){
                return a.custo < b.custo; 
            });

            float menor = custos[0].custo;
            float maior = custos.back().custo;

            float limite_grasp = valor_grasp(menor, maior);

            restricts.clear();
            for(unsigned int j=0 ; j<custos.size() ; j++){
                if(custos[j].custo <= limite_grasp){
                    restricts.push_back(custos[j].indice);
                }
            }

            // escolhe a operacao(retornando o indice), aloca na solucao e remove do vetor 
            int index = choose_schedule(jobs_temp, restricts);

            solution.aloca_tarefa(jobs_temp[restricts[index]][0]);
            remove_choosed_schedule(jobs_temp, restricts[index]);
        }

        int atraso = evaluator.evaluate_solution(solution);
//        cout << atraso << endl;
        this->media_atraso += atraso;
    }

    // Calcula a media de atraso das solucoes geradas
    this->media_atraso /= this->repeat;
    return solution;

}

void Constructive::remove_choosed_schedule(ScheduleMatrix& jobs_temp, int jobId){
    // remove a primeira operacao do jobId - foi a operacao inserida na solucao

	jobs_temp[jobId].erase(jobs_temp[jobId].begin());
	if(jobs_temp[jobId].empty()){
		// Caso ja tenha alocado todas as tarefas do job, elimina o job da matriz
		jobs_temp.erase(jobs_temp.begin()+jobId);
	}
}

int Constructive::choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts){
    return RandGen::randomInt((int)restricts.size());
}

float Constructive::valor_grasp(const float& min, const float& max){
	// 0 -> Greedy
	// 1 -> Random
    return (float) (min + alpha*(max-min));
    //return (float) (max + alpha*(min-max));
}

void Constructive::print(){
    for(int i=0 ; i<solution.size() ; i++){
        cout << "MACHINE " << i << ": ";
        for(unsigned int j=0 ; j<solution[i].size() ; j++){
            cout << "(" << solution[i][j].job << "," << solution[i][j].operation << "," << solution[i][j].time_execution << ") - ";
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

int Constructive::get_atraso(){ 
    return this->media_atraso;
}
