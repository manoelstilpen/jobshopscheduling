#include <LocalSearches/BestImprovement.hpp>
#include <Config.hpp>
#include "Grasp.hpp"

Grasp::Grasp() : Metaheuristic(){
}

Grasp::Grasp(double _alpha) : Metaheuristic(),
    alpha(_alpha) {
}

void Grasp::print_method_informations(){
	cout << "=========================================================================================" << endl;
	cout << " -> GRASP <- " << endl;
	cout << "ALPHA: " << this->alpha << endl;
}

Solution Grasp::apply(){

	print_method_informations();

	int maxIter = 3000;

	iterTotal = maxIter;
	iterAtual = 0;

	melhorAtraso = 0;

    // repeat é usado para repetir o método várias vezes. Por padrão seu valor é 1.
	for(int l = 0 ; l<Config::repeat ; l++){

		ConstructiveGraph constructive(0);
		Solution s0 = constructive.apply(); // constroi solucao inicial gulosa

		bestSolution = refinement(s0); // busca local na solucao inicial
		melhorAtraso = atrasoInicial = evaluator.evaluate_by_graph(bestSolution);

		constructive.set_alpha(0.3);

		while(iterAtual < maxIter){
			solution = constructive.apply();
	//		cout << "Inicial: " << evaluator.evaluate_by_graph(solution) << endl;
			solution = refinement(solution);

			int atraso = evaluator.evaluate_by_graph(solution);
	//		cout << "Refino: " << atraso << endl << endl;
			if(atraso < melhorAtraso){
				melhorAtraso = atraso;
				bestSolution = solution;
			}

			iterAtual++;

			if(Config::printProgress)
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

void Grasp::print(){
	cout << endl;
	cout << "MELHOR ATRASO: " << melhorAtraso << endl;
	bestSolution.print_solution();
}

void Grasp::print_graphic(){
	//cout << alpha << " " << media_atraso << endl;
}