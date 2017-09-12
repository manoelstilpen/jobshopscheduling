#include "FirstImprovement.hpp"

FirstImprovement::FirstImprovement(Solution sol) : Movement(sol){
    
}

FirstImprovement::FirstImprovement(){

}

void FirstImprovement::print_method_informations(){
    cout << "==========================================================================================" << endl;
    cout << " -> FIRST IMPROVEMENT <- " << endl;
}

Solution FirstImprovement::apply(){

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

        int randomBlock = 0;
        houveMelhora = false;
        atraso = INF;
        for(int i=0 ; i<couldMove.size() ; i++){

            int randomEdge = rand() % couldMove[randomBlock].size();
            invert(couldMove[randomBlock][randomEdge].index);

//            cout << "TROCANDO " << couldMove[randomEdge].source.index << "-" << couldMove[randomEdge].destination.index << endl;
            atraso = evaluator.evaluate_by_graph(graph);

            if(atraso < melhorAtraso)
            {
                // em caso de melhora aceita a solucao
                melhorAtraso = atraso;
//                cout << melhorAtraso << endl;
                bestSolution.setSolution(graph.generate_gantt());
                bestSolution.setGraph(graph);
                houveMelhora = true;
                break;
            }
            else 
            {
                // no caso de piora, reverte o movimento
                undo_last_movement();
                randomBlock++;
            }
        }

    } while(houveMelhora);

//    print();

    return bestSolution;
}   