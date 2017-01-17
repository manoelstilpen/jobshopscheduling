#include "ConstructiveGreedy.hpp"

ConstructiveGreedy::ConstructiveGreedy(){
	this->alpha = 0.5;
	this->repeat = 1;
}

ConstructiveGreedy::ConstructiveGreedy(ProblemInstance p, double alpha){
	this->alpha = alpha;
	this->instance = p;
	this->repeat = 1;
	this->evaluator.set_instance(this->instance);
}

Solution ConstructiveGreedy::generate_solution(){
	srand(time(NULL));

	this->jobs = instance.get_vec_schedules();
	int nMachines = instance.get_num_machines();
	int nJobs = instance.get_num_jobs();
	int nTasks = instance.get_num_tasks();

	media_atraso = 0;

	for(int i=0 ; i<this->repeat ; i++){

		// inicia a solucao
		machines.resize(nJobs);

		for (int m = 0; m < nMachines; m++){ // Allocation for each machine (one per one)
			int sumTasks = 0;
		
			for (int t = 0; t < nTasks; t++){
				vector<Schedule> tasks;

				// percorre os jobs e coloca no vetor todas as tarefas da maquina m
				for (int j = 0; j < nJobs; j++){
					int machineID = jobs[j][t].machine; // retorna a maquina referente a task t do job j
					if(machineID == m){ // Check the Machine Compatibility
						tasks.push_back(jobs[j][t]);
					}
				}

				int nTasksToBeAllocated = tasks.size();

				if (nTasksToBeAllocated > 0) {
					// ordena do menor para o maior tempo
					sort(tasks.begin(), tasks.end(), compara_tempo);

					for(int x = 0; x < nTasksToBeAllocated; x++){
						int sizeLC = ceil(this->alpha * tasks.size()); // ceil -> rounds up
						int randomized = rand() % sizeLC;			
						//cout << sizeLC << " " << randomized << endl;
						machines = aloca_tarefa(&machines, &(this->jobs), tasks[randomized]);
						tasks.erase(tasks.begin() + randomized);
					}
				}
			}
		}

		media_atraso += evaluator.evaluate_solution(machines);
	}

	this->media_atraso /= this->repeat;

	return machines;
}

void ConstructiveGreedy::set_instance(ProblemInstance problem){
	this->instance = problem;
}

void ConstructiveGreedy::set_repeat(int r){
	this->repeat = r;
}

int ConstructiveGreedy::get_atraso(){
	return this->media_atraso;
}

void ConstructiveGreedy::print(){
	for(int i=0 ; i<instance.get_num_jobs() ; i++){
		cout << "MACHINE " << i << ": ";
		for(int j=0 ; j<instance.get_num_tasks(); j++){
			cout << "(" << machines[i][j].job << "," << machines[i][j].task << "," << machines[i][j].time_execution << ") - ";
		}
		cout << endl;
	}

	evaluator.print();
}

void ConstructiveGreedy::print_graph(){
	cout << this->alpha << "\t" << this->media_atraso << endl;
}