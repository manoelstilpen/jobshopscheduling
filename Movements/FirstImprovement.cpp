#include "FirstImprovement.hpp"

FirstImprovement::FirstImprovement(Solution sol) : Movement(sol){
    
}

FirstImprovement::FirstImprovement(){

}

Solution FirstImprovement::apply(){

    bestSolution = solution;

    graph.bellmanFord();

    melhorAtraso = evaluator.evaluate_by_graph(graph);
    atrasoInicial = melhorAtraso;

    int atraso;
    do {

        updateCouldMove();

        if(couldMove.size() == 0) break;

        int randomEdge = 0;
        atraso = INF;
        for(int i=0 ; i<couldMove.size() ; i++){

            graph.invert(couldMove[randomEdge].index);
//            cout << "TROCANDO " << couldMove[randomEdge].source.index << "-" << couldMove[randomEdge].destination.index << endl;
            atraso = evaluator.evaluate_by_graph(graph);

            if(atraso < melhorAtraso)
            {
                // em caso de melhora aceita a solucao
                melhorAtraso = atraso;
  //              cout << melhorAtraso << endl;
                bestSolution.setSolution(graph.generate_gantt());
                bestSolution.setGraph(graph);
                break;
            }
            else 
            {
                // no caso de piora, reverte o movimento
                graph.invert(couldMove[randomEdge].index);
                randomEdge++;
            }
        }

    } while(atraso == melhorAtraso);

    print();
}   