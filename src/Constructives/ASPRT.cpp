#include "ASPRT.hpp"

ASPRT::ASPRT(ProblemInstance instance, double _alpha) : 
    Constructive(instance, _alpha) {

}

void ASPRT::print_method_informations(){

}

float ASPRT::define_priority(Schedule op){
    // Retorna o tempo de folga ou atraso da operacao

	// tempo de conclusao da operacao caso fosse inserida
	int remainingTime = solution.time_can_be_alocated(op) + op.time_execution;
	
	// subtrai da data de entrega do job
	remainingTime -= instance.get_due_times()[op.job];
	
	// caso seja menor do que 0, significa que nao há atraso no job ate o momento
	if(remainingTime < 0) remainingTime = 0;

	return remainingTime;
}

int ASPRT::choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts){
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