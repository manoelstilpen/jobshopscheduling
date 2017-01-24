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
	} else if(pos1Index == pos2Index){
		return this->solution;
	}

	Schedule tarefa1 = this->solution[machineNumber][pos1Index];
	Schedule tarefa2 = this->solution[machineNumber][pos2Index];

	if(pos1Index == 0){

		Schedule tarefaAnterior;
		int tempoTaskAnterior;

		tarefaAnterior = this->solution[machineNumber][pos2Index-1];
		tarefa1.time_execution = tarefaAnterior.time_execution + jobs[tarefa1.job][tarefa1.task].time_execution;
		this->solution[machineNumber][pos2Index] = tarefa1;

		tempoTaskAnterior = tarefa1.time_execution;
		for(int i=pos2Index+1 ; i<this->solution[machineNumber].size() ; i++){
			Schedule aux = this->solution[machineNumber][i];
			aux.time_execution = tempoTaskAnterior + jobs[aux.job][aux.task].time_execution;
			this->solution[machineNumber][i] = aux;
			tempoTaskAnterior = aux.time_execution;
		}

		// Como tarefa2 sera inserida na primeira posicao, logo, nao existe tempo acumulado
		tarefa2 = jobs[tarefa2.job][tarefa2.task];
		tarefa2.time_execution = jobs[tarefa2.job][tarefa2.task].time_execution;
		this->solution[machineNumber][pos1Index] = tarefa2;

		// Atualiza o tempo acumulado das tarefas seguintes
		tempoTaskAnterior = tarefa2.time_execution;
		for(int i=pos1Index+1 ; i<this->solution[machineNumber].size() ; i++){
			Schedule aux = this->solution[machineNumber][i];
			aux.time_execution = tempoTaskAnterior + jobs[aux.job][aux.task].time_execution;
			this->solution[machineNumber][i] = aux;
			tempoTaskAnterior = aux.time_execution;
		}


	} else {
		// Primeiro posiciona a tarefa1
		Schedule tarefaAnterior;
		int tempoTaskAnterior;

		tarefaAnterior = this->solution[machineNumber][pos2Index-1];
		tarefa1.time_execution = tarefaAnterior.time_execution + jobs[tarefa1.job][tarefa1.task].time_execution;
		this->solution[machineNumber][pos2Index] = tarefa1;

		tempoTaskAnterior = tarefa1.time_execution;
		for(int i=pos2Index+1 ; i<this->solution[machineNumber].size() ; i++){
			Schedule aux = this->solution[machineNumber][i];
			aux.time_execution = tempoTaskAnterior + jobs[aux.job][aux.task].time_execution;
			this->solution[machineNumber][i] = aux;
			tempoTaskAnterior = aux.time_execution;
		}

		// Posiciona a tarefa2
		tarefaAnterior = this->solution[machineNumber][pos1Index-1];
		tarefa2.time_execution = tarefaAnterior.time_execution + jobs[tarefa2.job][tarefa2.task].time_execution;
		this->solution[machineNumber][pos1Index] = tarefa2;

		tempoTaskAnterior = tarefa2.time_execution;
		for(int i=pos1Index+1 ; i<this->solution[machineNumber].size() ; i++){
			Schedule aux = this->solution[machineNumber][i];
			aux.time_execution = tempoTaskAnterior + jobs[aux.job][aux.task].time_execution;
			this->solution[machineNumber][i] = aux;
			tempoTaskAnterior = aux.time_execution;
		}

	}

	//cout << "SOLUCAO GERADA MOVIMENTO" << endl;
	//print_solution(this->solution);

	fix_solution();

	return this->solution;
}

void DeltaMoveExchange::fix_solution(){
	int nJobs = this->instance.get_num_jobs();
	int nTasks = this->instance.get_num_tasks();

	int it = 1;
	Evaluator eval(this->instance);
	//while(eval.testa_solucao(this->solution) == false){
	for(int k=0 ; k<2 ; k++){
		it++;

		for(int i=0 ; i<nJobs ; i++){
			for(int j=1 ; j<nTasks ; j++){

				Schedule tarefa = jobs[i][j];
				Schedule tarefa_solution = this->solution[tarefa.machine][0];
				int ultimaMaquina = jobs[i][j-1].machine;
				int tempoAcumuladoMachine;
				int tempoAcumuladoJob;

				// Procura pelo instante de termino da ultima tarefa do JOB i
				for(int l=0 ; l<this->solution[ultimaMaquina].size() ; l++){
					if(this->solution[ultimaMaquina][l].job == tarefa.job){
						tempoAcumuladoJob = this->solution[ultimaMaquina][l].time_execution;
						break;
					}
				}

				// Procura pelo instante de termino da tarefa antes da atual
				tempoAcumuladoMachine = 0;
				for(int l=1 ; l<this->solution[tarefa.machine].size() ; l++){
					if(this->solution[tarefa.machine][l].job == tarefa.job){
						tempoAcumuladoMachine = this->solution[tarefa.machine][l-1].time_execution;
						tarefa_solution = this->solution[tarefa.machine][l];
						break;
					}
				}

				int instanteInicio = (tarefa_solution.time_execution-jobs[i][j].time_execution);

				//cout << "a " << tempoAcumuladoJob << " " << tempoAcumuladoMachine <<" " << instanteInicio << endl;
				if(tempoAcumuladoJob <= instanteInicio && tempoAcumuladoMachine <= instanteInicio){
					//cout << "TUDO OK " << endl;

				} else {
					
					tarefa.time_execution += tempoAcumuladoJob;

					if(tarefa.time_execution < tempoAcumuladoMachine){
						tarefa.time_execution += (tempoAcumuladoMachine - tarefa.time_execution);
					}

					//cout << "time " << tarefa.time_execution << endl;

					int index;
					for(int l=0 ; l<this->solution[tarefa.machine].size() ; l++){
						if(this->solution[tarefa.machine][l].job == tarefa.job){
							//print_schedule(tarefa);
							//cout << endl;
							this->solution[tarefa.machine][l] = tarefa;
							index = l;
							break;
						}
					}

					//print_solution(this->solution);

					for(int l=index+1 ; l<this->solution[tarefa.machine].size() ; l++){
						Schedule aux = this->solution[tarefa.machine][l];
						int tempoInicioAux = aux.time_execution - jobs[aux.job][aux.task].time_execution;

						if(tempoInicioAux < this->solution[tarefa.machine][l-1].time_execution){
							aux.time_execution = this->solution[tarefa.machine][l-1].time_execution + jobs[aux.job][aux.task].time_execution;
							this->solution[tarefa.machine][l] = aux;
						} else {
							// caso tenha janela, aumentar o tempo de uma tarefa anterior nao implicara nas seguintes
							break;
						}
					}


				}
				print_solution(this->solution);
			}
		}
	}
	cout << "it: " << it << endl;
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