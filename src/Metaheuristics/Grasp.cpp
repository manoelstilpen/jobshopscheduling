#include "Grasp.hpp"

Grasp::Grasp() : Metaheuristic(){
}

Grasp::Grasp(ProblemInstance instance, double _alpha) : Metaheuristic(instance),
    alpha(_alpha) {

}

void Grasp::print_method_informations(){
	cout << "=========================================================================================" << endl;
	cout << " -> GRASP <- " << endl;
	cout << "ALPHA: " << this->alpha << endl;
}

Solution Grasp::apply(){
	srand(time(0));	

//	print_method_informations();

	int maxIter = 3000;
	int atraso = 0;

	iterTotal = maxIter;
	iterAtual = 0;

	melhorAtraso = 0;

	for(int l = 0 ; l<repeat ; l++){

		ConstructiveGraph constructive(instance, 0); 
		Solution s0 = constructive.apply(); // constroi solucao inicial gulosa

		bestSolution = refinement(s0); // busca local na solucao inicial
		melhorAtraso = atrasoInicial = evaluator.evaluate_by_graph(bestSolution);

		constructive.setAlpha(0.4);

		while(iterAtual < maxIter){
			solution = constructive.apply();
			solution = refinement(solution);

			int atraso = evaluator.evaluate_by_graph(solution);
			if(atraso < melhorAtraso){
				melhorAtraso = atraso;
				bestSolution = solution;
			}

			iterAtual++;

			print_progress();
		}
	}

	return bestSolution;
}

Solution Grasp::refinement(Solution& s){
	local_search = new FirstImprovement(s);
	solution = local_search->apply();

	return solution;
}

void Grasp::print_graphic(){
	//cout << alpha << " " << media_atraso << endl;
}