#include "GraphExchange.hpp"

GraphExchange::GraphExchange(){

}

GraphExchange::GraphExchange(Solution sol){
    this->solution = sol;
    this->graph = sol.getGraph();
    this->instance = sol.getInstance();
    this->evaluator.set_instance(this->instance);
}

void GraphExchange::apply(){

    Solution bestSolution = solution;

    graph.bellmanFord();

    int melhorAtraso = evaluator.evaluate_by_graph(graph);
    int inicial = melhorAtraso;

    for(int c=0 ; c<1000 ; c++)
    {
        
        updateCouldMove();

        int randomEdge = rand() % couldMove.size();

//        cout << "TROCANDO " << couldMove[randomEdge].source.job << "-" << couldMove[randomEdge].source.operation <<
//        " com " << couldMove[randomEdge].destination.job << "-" << couldMove[randomEdge].destination.operation << endl;
        graph.invert(couldMove[randomEdge].index);

//        Solution::print_solution(graph.generate_gantt());

        int atraso = evaluator.evaluate_by_graph(graph);
//        cout << "ATRASO: " << atraso << endl;
        if(atraso < melhorAtraso){
            melhorAtraso = atraso;
            bestSolution.setSolution(graph.generate_gantt());
            bestSolution.setGraph(graph);
        }        
    }

    float perc = percent_between(inicial, melhorAtraso);

    cout << endl;
    cout << "INICIAL: " << inicial << endl;
    cout << "MELHOR: " << melhorAtraso << " (" << perc << "%)" << endl;
    bestSolution.print_solution();
    
}

void GraphExchange::updateCouldMove(){
    // atualiza o caminho critico e as arestas passiveis de troca
    criticalPath = graph.bellmanFord();

    couldMove.clear();

    for(int i=0 ; i<instance.get_num_jobs() ; i++)
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

    /*
        cout << "ARESTAS QUE PODEM MOVER: " << endl;
        for(int i=0 ; i<couldMove.size() ; i++)
        {
            cout << "Job " << i << ": ";
            for(int j=0 ; j<couldMove[i].size() ; j++){
                cout << "(" << couldMove[i][j].source.index << " " << couldMove[i][j].destination.index << "), ";
            }
            cout << endl;
        }
    */
}