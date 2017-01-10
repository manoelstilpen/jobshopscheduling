#include "ConstructiveGreedy.hpp"

ConstructiveGreedy::ConstructiveGreedy(){
	alpha = 0.1;
}

ConstructiveGreedy::ConstructiveGreedy(double alpha){
	this->alpha = alpha;
}

Solution ConstructiveGreedy::generate_solution(){
	Solution machines;

	ScheduleMatrix jobs = instance.get_vec_schedules();
	int nMachines = instance.get_num_machines();
	int nJobs = instance.get_num_jobs();
	int nTasks = instance.get_num_tasks();

	// inicia a solucao
	machines.resize(nJobs);
	for(int i=0 ; i<nJobs ; i++){
		machines[i].resize(nTasks);
	}

	for (int m = 0; m < nMachines; m++){ // Allocation for each machine (one per one)
		int sumTasks = 0;
	
		for (int t = 0; t < nTasks; t++){
			vector<Schedule> tasks;

			//jobs sao compostos de tarefas
			//percorre o job e coloca as tarefas em suas devidas maquinas
			for (int j = 0; j < nJobs; j++){
				int machineID = jobs[j][t].machine; //retorna a maquina referente ao task t do job j
				if(machineID == m){ // Check the Machine Compatibility
					tasks.push_back(Schedule(jobs[j][t].job, jobs[j][t].task, jobs[j][t].time_execution)); // Schedule (job,task,time)
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
					machines[m][x + totalTasksAllocated].job = tasks[randomized].job; // Allocate the Task in its respectively Machine m
					machines[m][x + totalTasksAllocated].task = tasks[randomized].task;
					tasks.erase(tasks.begin() + randomized);
				}
			}
		}
	}

//	printSolution(nJobs, nTasks, machines);

	for(int i=0 ; i<nJobs ; i++){
		for(int j=0 ; j<nTasks ; j++){
			cout << "(" << machines[i][j].job << "," << machines[i][j].task << "," << jobs[machines[i][j].job][machines[i][j].task].time_execution << ") - ";
		}
		cout << endl;
	}

	return machines;
}



void ConstructiveGreedy::set_instance(ProblemInstance problem){
	this->instance = problem;
}