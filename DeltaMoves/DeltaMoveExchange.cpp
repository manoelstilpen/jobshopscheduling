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

	Evaluator eval(this->instance);
	//while(eval.testa_solucao(this->solution) == false){
	for(int k=0 ; k<100 ; k++){

		for(int i=0 ; i<nJobs ; i++){
			for(int j=1 ; j<nTasks ; j++){

				Schedule tarefa = jobs[i][j];
				int ultimaMaquina = jobs[i][j-1].machine;
				int tempoAcumuladoMachine;
				int tempoAcumuladoJob;

				// Procura pelo instante de termino da ultima tarefa do JOB
				for(int l=0 ; l<this->solution[ultimaMaquina].size() ; l++){
					if(this->solution[ultimaMaquina][l].job == tarefa.job){
						tempoAcumuladoJob = this->solution[ultimaMaquina][l].time_execution;
						break;
					}
				}

				// Procura pelo instante de termino da ultima tarefa antes da atual
				tempoAcumuladoMachine = tarefa.time_execution;
				for(int l=1 ; l<this->solution[tarefa.machine].size() ; l++){
					if(this->solution[tarefa.machine][l].job == tarefa.job){
						tempoAcumuladoMachine = this->solution[tarefa.machine][l-1].time_execution;
						break;
					}
				}

				if(tempoAcumuladoJob <= (tarefa.time_execution-jobs[i][j].time_execution) &&
					tempoAcumuladoMachine <= (tarefa.time_execution-jobs[i][j].time_execution)){


				} else {
					
					tarefa.time_execution = tempoAcumuladoJob + jobs[i][j].time_execution;

					if(tarefa.time_execution < tempoAcumuladoMachine){
						tarefa.time_execution += (tempoAcumuladoMachine - tarefa.time_execution);
					}

					int index;
					for(int l=0 ; l<this->solution[tarefa.machine].size() ; l++){
						if(this->solution[tarefa.machine][l].job == tarefa.job){
							this->solution[tarefa.machine][l] = tarefa;
							index = l;
							break;
						}
					}

					for(int l=index+1 ; l<this->solution[tarefa.machine].size() ;l++){
						Schedule aux = this->solution[tarefa.machine][l];
						aux.time_execution = (solution[aux.machine][l].time_execution + jobs[aux.job][aux.task].time_execution); 
						solution[tarefa.machine][i] = aux;
					}


				}
			}
		}
		//print_solution(this->solution);
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