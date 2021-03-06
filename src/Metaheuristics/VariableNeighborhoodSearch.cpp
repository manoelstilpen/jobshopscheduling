#include <Config.hpp>
#include "VariableNeighborhoodSearch.hpp"

VariableNeighborhoodSearch::VariableNeighborhoodSearch() : Metaheuristic(){

}

VariableNeighborhoodSearch::VariableNeighborhoodSearch(Solution s) : Metaheuristic(s){

}

Solution VariableNeighborhoodSearch::apply(){
    
    print_method_informations();

    vizinhancas.push_back(new FirstImprovement(solution)); // busca local do vns
    vizinhancas.push_back(new ShakeK(solution, 2));        // movimento mover 2 arcos
    vizinhancas.push_back(new ShakeK(solution, 3));        // movimento mover 3 arcos
    vizinhancas.push_back(new ShakeK(solution, 4));        // movimento mover 4 arcos

    auto criticalBlocks = graph.getCriticalPath();
    
    melhorAtraso = evaluator.evaluate_by_graph(graph);
    atrasoInicial = melhorAtraso;

    const int max_iter = 600;
    const int max_repeticoes = 4;
    const long r = vizinhancas.size();

    int iter_sem_melhora = 0;

    iterAtual = 0;
    iterTotal = max_iter * r * max_repeticoes;
    
    while(iter_sem_melhora < max_iter){
        iter_sem_melhora += 1;

        int vizinhanca_atual = 1;

        // enquanto houver vizinhancas
        while (vizinhanca_atual < r){

            // gerando um vizinho s' qualquer
            vizinhancas[vizinhanca_atual]->set_solution(solution);
            Solution s1 = vizinhancas[vizinhanca_atual]->apply();

            // aplicando busca local em s1
            vizinhancas[0]->set_solution(s1);
            Solution s2 = vizinhancas[0]->apply();

            int atraso = evaluator.evaluate_by_graph(s2);

            if ( atraso < melhorAtraso ) {
                // atualiza melhor solucao
                solution = s2;
                bestSolution = s2;
                melhorAtraso = atraso;
                vizinhanca_atual = 1;
                iter_sem_melhora = 0;
            } else {
                vizinhanca_atual++;
            }

            iterAtual++;

            if(Config::printProgress)
                print_progress();
        }
    }

    for(unsigned int i=0 ; i<vizinhancas.size() ; i++){
        delete vizinhancas[i];
    }

    return bestSolution;
}

void VariableNeighborhoodSearch::print_method_informations(){
    cout << "==========================================================================================" << endl;
    cout << " -> VARIABLE NEIGHBORHOOD SEARCH <- " << endl;
}