#include "BestImprovement.hpp"

BestImprovement::BestImprovement() : Movement(){

}

BestImprovement::BestImprovement(Solution s) : Movement(s){

}

void BestImprovement::print_method_informations(){
    cout << "==========================================================================================" << endl;
    cout << " -> BEST IMPROVEMENT <- " << endl;
}

Solution BestImprovement::apply(){
    
//    print_method_informations();

    bestSolution = solution;

    graph.bellmanFord();

    melhorAtraso = evaluator.evaluate_by_graph(graph);
    atrasoInicial = melhorAtraso;

    int atraso;
    bool houveMelhora = false;
    do {

        updateCouldMove();

        if(couldMove.size() == 0) break;

        houveMelhora = false;
        atraso = INF;
        for(int i=0 ; i<couldMove.size() ; i++){

            graph.invert(couldMove[i].index);
            lastMovements.push_back(couldMove[i].index);
            //cout << "TROCANDO " << couldMove[i].source.index << "-" << couldMove[i].destination.index << endl;
            atraso = evaluator.evaluate_by_graph(graph);

            if(atraso < melhorAtraso)
            {
                // em caso de melhora aceita a solucao
                melhorAtraso = atraso;
                bestSolution.setSolution(graph.generate_gantt());
                bestSolution.setGraph(graph);
                houveMelhora = true;
            }
            
            // refaz o movimento para poder avaliar as outras possibilidades
            undo_last_movement();
        }

    } while(houveMelhora);

//    print();
    return bestSolution;
}