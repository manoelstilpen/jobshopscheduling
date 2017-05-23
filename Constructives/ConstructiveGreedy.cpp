#include "ConstructiveGreedy.hpp"

ConstructiveGreedy::ConstructiveGreedy(){
	this->alpha = 0.5;
	this->repeat = 1;
}

ConstructiveGreedy::ConstructiveGreedy(ProblemInstance p, double alpha) : Constructive(p) {
	this->alpha = alpha;
}

void ConstructiveGreedy::print_method_informations(){
	cout << "=========================================================================================" << endl;
	cout << " -> CONSTRUCTIVE GREEDY <-" << endl;
}

Solution ConstructiveGreedy::apply(){

/*
 * NAO ESTA FUNCIONANDO. A INSERCAO PARA ESTE CASO NAO FUNCIONA
 */

	srand(time(NULL));

	this->media_atraso = 0;

	for(int i=0 ; i<this->repeat ; i++){

		// inicia a solucao
		solution.resize(nMachines);

		for (int m = 0; m < nMachines; m++){ // Allocation for each machine (one per one)
			int sumTasks = 0;
		
			for (int t = 0; t < nOperations; t++){
				vector<Schedule> operations;

				// percorre os jobs e coloca no vetor todas as tarefas da maquina m
				for (int j = 0; j < nJobs; j++){
					int machineID = instance[j][t].machine; // retorna a maquina referente a task t do job j
					if(machineID == m){ // Check the Machine Compatibility
						operations.push_back(instance[j][t]);
					}
				}

				int nTasksToBeAllocated = operations.size();

				if (nTasksToBeAllocated > 0) {
					// ordena do menor para o maior tempo
					sort(operations.begin(), operations.end(), compara_tempo);

					for(int x = 0; x < nTasksToBeAllocated; x++){
						int sizeLC = ceil(this->alpha * operations.size()); // ceil -> rounds up
						int randomized = rand() % sizeLC;			
//						cout << "ESHOLGIDA: " << operations[randomized].job << " " << operations[randomized].task << endl;
						solution.aloca_tarefa(operations[randomized]);
						operations.erase(operations.begin() + randomized);
					}
				}
			}
		}

		this->media_atraso += evaluator.evaluate_solution(solution);
	}

	this->media_atraso /= this->repeat;

	return solution;
}

void ConstructiveGreedy::print_graph(){
	cout << this->alpha << "\t" << this->media_atraso << endl;
}