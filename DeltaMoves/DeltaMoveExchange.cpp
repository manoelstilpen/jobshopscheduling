#include "DeltaMoveExchange.hpp"

DeltaMoveExchange::DeltaMoveExchange(){

}

DeltaMoveExchange::DeltaMoveExchange(ProblemInstance p, Solution solution, int machine, int pos1, int pos2){
	set_instance(p);
	set_solution(solution);
	set_positions(machine, pos1, pos2);
}

DeltaMoveExchange::DeltaMoveExchange(int machine, int pos1, int pos2){
	set_positions(machine, pos1, pos2);
}

DeltaMoveExchange::DeltaMoveExchange(ProblemInstance p){
	set_instance(p);
}

Solution DeltaMoveExchange::apply_exchange_move(){

	// Armazena o indice maior na pos2
	if(pos1Index > pos2Index){
		int aux = pos1Index;
		pos1Index = pos2Index;
		pos2Index = aux;
	}

	Schedule tarefa1 = this->solution[machineNumber][pos1Index];
	Schedule tarefa2 = this->solution[machineNumber][pos2Index];

	if(pos1Index == 0){
		// Como tarefa2 sera inserida na primeira posicao, logo, nao existe tempo acumulado
		cout << tarefa2.job << " " << tarefa2.task << endl;
		tarefa2.time_execution = jobs[tarefa2.job][tarefa2.task].time_execution;
		this->solution[machineNumber][pos1Index] = tarefa2;

		// Atualiza o tempo final da tarefa1
		tarefa1.time_execution = this->solution[machineNumber][pos2Index-1].time_execution + jobs[tarefa1.job][tarefa1.task].time_execution;
		this->solution[machineNumber][pos2Index] = tarefa1;

		// Atualiza o tempo acumulado das tarefas seguintes
		for(int i=pos2Index+1 ; i<this->solution[machineNumber].size() ; i++){
			Schedule aux = this->solution[machineNumber][i];
			aux.time_execution = jobs[aux.job][aux.task].time_execution + this->solution[machineNumber][i-1].time_execution;
			this->solution[machineNumber][i] = aux;
		}

	} else {
		// Primeiro posiciona a tarefa1
		int tempoTaskAnterior;
		tempoTaskAnterior = this->solution[machineNumber][pos2Index-1].time_execution;
		tarefa1.time_execution = jobs[tarefa1.job][tarefa1.task].time_execution + tempoTaskAnterior;
		this->solution[machineNumber][pos2Index] = tarefa1;

		// Ajusta o tempo das tarefas sequentes
		for(int i=pos2Index+1 ; i<this->solution[machineNumber].size() ; i++){
			Schedule aux = this->solution[machineNumber][i];
			aux.time_execution = this->solution[machineNumber][i-1].time_execution + jobs[aux.job][aux.task].time_execution;
			this->solution[machineNumber][i] = aux;
		}

		// Posiciona a tarefa2
		tempoTaskAnterior = this->solution[machineNumber][pos1Index-1].time_execution;
		tarefa2.time_execution = jobs[tarefa2.job][tarefa2.task].time_execution + tempoTaskAnterior;
		this->solution[machineNumber][pos1Index] = tarefa2;

		// Ajusta o tempo das tarefas sequentes
		for(int i=pos1Index+1 ; i<this->solution[machineNumber].size() ; i++){
			Schedule aux = this->solution[machineNumber][i];
			aux.time_execution = this->solution[machineNumber][i-1].time_execution + jobs[aux.job][aux.task].time_execution;
			this->solution[machineNumber][i] = aux;
		}
	}

	fix_solution();

	return this->solution;
}

void DeltaMoveExchange::fix_solution(){
	int nJobs = this->instance.get_num_jobs();
	int nTasks = this->instance.get_num_tasks();

	for(int k=0 ; k<nJobs*nTasks ; k++){

		for(int i=0 ; i<nJobs ; i++){
			for(int j=1 ; j<nTasks ; j++){

				Schedule tarefa = jobs[i][j];
				int ultimaMaquina = jobs[i][j-1].machine;
				int tempoAcumulado;

				for(int l=0 ; l<this->solution[ultimaMaquina].size() ; l++){
					if(this->solution[ultimaMaquina][l].job == tarefa.job){
						tempoAcumulado = this->solution[ultimaMaquina][l].time_execution;
						break;
					}
				}

				if(tempoAcumulado <= (tarefa.time_execution-jobs[i][j].time_execution)){
					// OK ATE AQUI
				} else {
					tarefa.time_execution = tempoAcumulado + jobs[i][j].time_execution;

					bool achou = false;
					for(int l=0 ; l<this->solution[tarefa.machine].size() ; l++){

						if(achou){
							Schedule aux = solution[tarefa.machine][l];
							this->solution[tarefa.machine][l].time_execution = jobs[aux.job][aux.task].time_execution + this->solution[tarefa.machine][l-1].time_execution;
						}

						if(this->solution[tarefa.machine][l].job == tarefa.job){
							this->solution[tarefa.machine][l] = tarefa;
							achou = true;
						}

					}
				}
			}
		}
	}
}

void DeltaMoveExchange::set_instance(ProblemInstance i){
	this->instance = i;
	this->jobs = this->instance.get_vec_schedules();
}

void DeltaMoveExchange::set_solution(Solution sol){
	this->solution = sol;
}

void DeltaMoveExchange::set_positions(int mach, int pos1, int pos2){
	set_machine_number(mach);
	set_pos1(pos1);
	set_pos2(pos2);
}

void DeltaMoveExchange::set_machine_number(int machine){
	this->machineNumber = machine;
}

void DeltaMoveExchange::set_pos1(int num){
	this->pos1Index = num;
}

void DeltaMoveExchange::set_pos2(int num){
	this->pos2Index = num;
}