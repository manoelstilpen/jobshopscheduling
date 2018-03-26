//
// Created by manoel on 22/03/18.
//

#include <BestImprovement.hpp>

BestImprovement::BestImprovement(Solution s) : Metaheuristic(s){}

void BestImprovement::print_method_informations() {
    cout << "==========================================================================================" << endl;
    cout << " -> BEST IMPROVEMENT <- " << endl;
}

Solution BestImprovement::apply() {

    bestSolution = solution;
    atrasoInicial = melhorAtraso = evaluator.evaluate_by_graph(graph);

    int atraso;
    bool houveMelhora;

    for(int tentativas=0 ; tentativas<3 ; tentativas++) {

        do {

            auto criticalBlocks = graph.getCriticalBlocks();
            if (criticalBlocks.empty()) break;

            houveMelhora = false;

            for (const auto &block : criticalBlocks) {

                if (tentativas == 0){
                    // inverter a primeira aresta do bloco
                    invert(block[0]);
                } else if (tentativas == 1){
                    // inverter a ultima aresta do bloco
                    invert(block.back());
                } else {
                    // escolher uma aresta aleatoria para mover
                    unsigned long random = rand() % block.size();
                    invert(block[random]);
                }

                atraso = evaluator.evaluate_by_graph(graph);

                if (atraso < melhorAtraso) {
                    melhorAtraso = atraso;
                    bestSolution.setGraph(graph);
                    houveMelhora = true;
                }

                graph.undo_last_movement();
            }

        } while (houveMelhora);
    }

    return bestSolution;
}
