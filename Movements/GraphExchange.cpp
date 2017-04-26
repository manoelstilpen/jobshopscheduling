#include "GraphExchange.hpp"

GraphExchange::GraphExchange(){

}

GraphExchange::GraphExchange(Solution sol) : Movement(sol){
    couldMoveTime = evaluateTime = invertTime = 0;
}

Solution GraphExchange::apply(){

    bestSolution = solution;

    graph.bellmanFord();

    melhorAtraso = evaluator.evaluate_by_graph(graph);
    atrasoInicial = melhorAtraso;

//    while(true){
    clock_t totalAbsolute = clock();
    for(int i=0 ; i<100 ; i++){

        clock_t inicio = clock();
        updateCouldMove();
        couldMoveTime += (double) (clock() - inicio)/CLOCKS_PER_SEC;

        if(couldMove.size() == 0) break;

        int randomEdge = rand() % couldMove.size();

        cout << "TROCANDO " << couldMove[randomEdge].source.index << "-" << couldMove[randomEdge].destination.index << endl;

        inicio = clock();
        graph.invert(couldMove[randomEdge].index);
        invertTime += (double) (clock() - inicio)/CLOCKS_PER_SEC;

//        Solution::print_solution(graph.generate_gantt());
        inicio = clock();
        int atraso = evaluator.evaluate_by_graph(graph);
        evaluateTime += (double) (clock() - inicio)/CLOCKS_PER_SEC;

//        cout << "ATRASO: " << atraso << endl;
        if(atraso < melhorAtraso){
            melhorAtraso = atraso;
            cout << melhorAtraso << " " << i << endl;
            bestSolution.setSolution(graph.generate_gantt());
            bestSolution.setGraph(graph);
        }
            
    }

    print();
    cout << "CouldMove: " << couldMoveTime << endl;
    cout << "Evaluate:  " << evaluateTime << endl;
    cout << "Inverting:  " << invertTime << endl;
    cout << "Total:     " << (double) (clock() - totalAbsolute)/CLOCKS_PER_SEC << endl;
}

/*void GraphExchange::updateCouldMove(){
    // atualiza o caminho critico e as arestas passiveis de troca
    criticalPath = graph.bellmanFord();

    couldMove.clear();

    for(int i=0 ; i<criticalPath.size() ; i++)
    {
        if(criticalPath[i].size() > 1)
        {
            for(int j=0 ; j<criticalPath[i].size() ; j++)
            {
                if(criticalPath[i][j].source.job != criticalPath[i][j].destination.job && 
                    criticalPath[i][j].source.job != -1 && criticalPath[i][j].destination.job != -1)
                {
                    couldMove.push_back(criticalPath[i][j]);
                }
            }
        }
    }        

    //printCouldMove();

}*/