#include <RandGen.hpp>
#include "FirstImprovement.hpp"

FirstImprovement::FirstImprovement(Solution sol) : Metaheuristic(sol){
    
}

void FirstImprovement::print_method_informations(){
    cout << "==========================================================================================" << endl;
    cout << " -> FIRST IMPROVEMENT <- " << endl;
}

Solution FirstImprovement::apply(){

//    print_method_informations();

    bestSolution = solution;

    melhorAtraso = evaluator.evaluate_by_graph(graph);  
    atrasoInicial = melhorAtraso;

    int atraso;
    bool houveMelhora;

    for(int tentativas=0 ; tentativas < 3 ; tentativas++) {

        do {
            //        graph.printGraph();
            auto criticalBlocks = graph.getCriticalBlocks();
            //        graph.printCriticalPath();
            //        graph.printCriticalBlock();

            if (criticalBlocks.empty()) break;

            uint randomBlock = 0;
            houveMelhora = false;

            for (const auto& block : criticalBlocks) {

                if(tentativas == 0){
                    // primeira tentativa: inverte a primeira aresta do bloco
                    invert(block[0]);
                } else if(tentativas == 1){
                    // segunda tentativa: inverte a ultima aresta do bloco
                    invert(block.back());
                } else {
                    // ultima tentativa: inverte uma aresta aleatoria do bloco
                    int randomEdge = RandGen::randomInt((int)block.size());
                    invert(block[randomEdge]);
                }


                atraso = evaluator.evaluate_by_graph(graph);

                if (atraso < melhorAtraso) {
                    // em caso de melhora aceita a solucao
                    melhorAtraso = atraso;
                    bestSolution.setGraph(graph);
                    houveMelhora = true;
                    break;

                } else {
                    // no caso de piora, reverte o movimento e avança para outro bloco critico
                    graph.undo_last_movement();
                    randomBlock++;
                }

                //            graph.printGraph();

            }

        } while (houveMelhora);
    }

    return bestSolution;
}   