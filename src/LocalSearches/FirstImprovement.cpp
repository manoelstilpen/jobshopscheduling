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

    melhorAtraso = evaluator.evaluate_by_graph(graph);  
    atrasoInicial = melhorAtraso;

    int atraso;
    bool houveMelhora;
    
    do {
//        graph.printGraph();
        auto criticalBlocks = graph.getCriticalBlocks();
//        graph.printCriticalBlock();

        if(criticalBlocks.empty()) break;

        uint randomBlock = 0;
        houveMelhora = false;

        for(unsigned int i=0 ; i<criticalBlocks.size() ; i++){

            ulong randomEdge = rand() % criticalBlocks[randomBlock].size();
            invert(criticalBlocks[randomBlock][randomEdge]);

            atraso = evaluator.evaluate_by_graph(graph);

            if(atraso < melhorAtraso){
                // em caso de melhora aceita a solucao
                melhorAtraso = atraso;
                bestSolution.setGraph(graph);
                houveMelhora = true;
                break;

            } else {
                // no caso de piora, reverte o movimento
                graph.undo_last_movement();
                randomBlock++;
            }

//            graph.printGraph();

        }

    } while(houveMelhora);
    
    return bestSolution;
}   