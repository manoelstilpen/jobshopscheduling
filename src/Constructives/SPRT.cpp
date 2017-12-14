#include "SPRT.hpp"

SPRT::SPRT(){

}

SPRT::SPRT(ProblemInstance p, double _alpha) : Constructive(p, _alpha) {

}

void SPRT::print_method_informations(){
    cout << "=========================================================================================" << endl;
	cout << " -> CONSTRUCTIVE SPRT <-" << endl;
    cout << "ALPHA: " << this->alpha << endl;
}

/*
 * GRASP CONSTRUCTIVE
 * Cria solucao considerando o custo das tarefas.
 * Aloca aquela que possuir o menor custo na solucao apos ser inserida
 * Em caso de empate de tarefas, opta-se por aquela que se inserida, deixa o menor tempo acumulado em sua maquina
 */
float SPRT::define_priority(Schedule op){
    // priority = s / RPT
	float s = instance.get_due_times()[op.job];
	s -= solution.time_can_be_alocated(op);

	float rpt = 0; // tempo de processamento restante 
	for(int i=op.task ; i<instance[op.job].size() ; i++){
		rpt += (solution.time_can_be_alocated(instance[op.job][i]) + instance[op.job][i].time_execution);
	}

	s -= rpt;

    return (float) (s / rpt); 
}

int SPRT::choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts){
    return rand() % restricts.size();
}