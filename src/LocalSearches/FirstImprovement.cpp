#include "FirstImprovement.hpp"

FirstImprovement::FirstImprovement(Solution sol) : Metaheuristic(sol){
    
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

        if(criticalBlocks.size() == 0) break;

        int randomBlock = 0;
        houveMelhora = false;
        atraso = INF;

        for(int i=0 ; i<criticalBlocks.size() ; i++){

            int randomEdge = rand() % criticalBlocks[randomBlock].size();
            invert(criticalBlocks[randomBlock][randomEdge]);

            atraso = evaluator.evaluate_by_graph(graph);

            if(atraso < melhorAtraso){
                // em caso de melhora aceita a solucao
                melhorAtraso = atraso;
                
                graph.bellmanFord();
                bestSolution.setSolution(graph.generate_gantt());
                bestSolution.setGraph(graph);

                houveMelhora = true;

                break;
            } else {
                // no caso de piora, reverte o movimento
                undo_last_movement();
                randomBlock++;
            }

        }

    } while(houveMelhora);
    
    return bestSolution;
}   