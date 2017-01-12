#include "ConstructiveGreedy.hpp"

ConstructiveGreedy::ConstructiveGreedy(){
	alpha = 0.1;
}

ConstructiveGreedy::ConstructiveGreedy(double alpha){
	this->alpha = alpha;
}

Solution ConstructiveGreedy::generate_solution(){
	srand(time(NULL));

	Solution machines;

	this->jobs = instance.get_vec_schedules();
	int nMachines = instance.get_num_machines();
	int nJobs = instance.get_num_jobs();
	int nTasks = instance.get_num_tasks();

	// inicia a solucao
	machines.resize(nJobs);

	for (int m = 0; m < nMachines; m++){ // Allocation for each machine (one per one)
		int sumTasks = 0;
	
		for (int t = 0; t < nTasks; t++){
			vector<Schedule> tasks;

			//jobs sao compostos de tarefas
			//percorre o job e coloca as tarefas em suas devidas maquinas
			for (int j = 0; j < nJobs; j++){
				int machineID = jobs[j][t].machine; //retorna a maquina referente ao task t do job j
				if(machineID == m){ // Check the Machine Compatibility
					tasks.push_back(jobs[j][t]);
				}
			}

			int nTasksToBeAllocated = tasks.size();

			//insere numa linha l da matriz todas as tasks referentes a maquina l
			if (nTasksToBeAllocated > 0) {
				// ordena do menor para o maior tempo
				sort(tasks.begin(), tasks.end(), compara_tempo);

				int totalTasksAllocated = sumTasks;
				sumTasks += nTasksToBeAllocated;

				for (int x = 0; x < nTasksToBeAllocated; x++) {
					int sizeLC = ceil(this->alpha * tasks.size()); // ceil -> rounds up
					int randomized = rand() % sizeLC;
					//machines[m][x + totalTasksAllocated] = tasks[randomized]; // Allocate the Task in its respectively Machine m
					machines = aloca_tarefa(machines, tasks[randomized]);
					tasks.erase(tasks.begin() + randomized);
				}
			}
		}
	}

//	printSolution(nJobs, nTasks, machines);

	for(int i=0 ; i<nJobs ; i++){
		cout << "MACHINE " << i << ": ";
		for(int j=0 ; j<nTasks ; j++){
			cout << "(" << machines[i][j].job << "," << machines[i][j].task << "," << machines[i][j].time_execution << ") - ";
		}
		cout << endl;
	}

	return machines;
}

Solution ConstructiveGreedy::aloca_tarefa(Solution solution, Schedule tarefa){
	int machine = tarefa.machine;
	int nTasks = instance.get_num_tasks();
	int sizeMachine = (solution)[machine].size(); // quantidade de tasks alocadas na maquina

	if(tarefa.task == 0){
		// se for a primeira tarefa do job, nao e necessario analisar as tasks anteriores
		if((solution)[machine].size() == 0){
			// como nao tem outra tarefa alocada nessa maquina, apenas insere
			(solution)[machine].push_back(tarefa);
		} else {
			int tempo = (solution)[machine][sizeMachine-1].time_execution; // armazena o tempo acumulado
			tarefa.time_execution += tempo; // adiciona o tempo acumulado
			(solution)[machine].push_back(tarefa);
		}

	} else {

		// maquina que foi executada a ultima task do job
		int lastMachine = jobs[tarefa.job][tarefa.task-1].machine;
		int timeLastTask = 0;
		// procura pelo instante que a ultima task DO JOB foi finalizada
		for(int i=0 ; i<(solution)[lastMachine].size() ; i++){
			if((solution)[lastMachine][i].job == tarefa.job){
				timeLastTask = (solution)[lastMachine][i].time_execution;
				break;
			}
		}

		// tempo acumulado da ultima tarefa DA MAQUINA executada
		int timeMachine = 0;
		if(sizeMachine != 0){
			timeMachine = (solution)[machine][sizeMachine-1].time_execution;
		}
		
		if(timeMachine > timeLastTask){
			// se o instante atual da maquina for maior que o instante em que a ultima task
			// do job terminou... esta ok
			tarefa.time_execution += (solution)[machine][sizeMachine-1].time_execution;
			(solution)[machine].push_back(tarefa);
		} else {
			tarefa.time_execution += timeLastTask;
			(solution)[machine].push_back(tarefa);
		}
	}

	return solution;
}


void ConstructiveGreedy::set_instance(ProblemInstance problem){
	this->instance = problem;
}