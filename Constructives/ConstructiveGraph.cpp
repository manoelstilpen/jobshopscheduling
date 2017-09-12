#include "ConstructiveGraph.hpp"

ConstructiveGraph::ConstructiveGraph() : Constructive(){

}

ConstructiveGraph::ConstructiveGraph(ProblemInstance p, double _a) : Constructive(p), alpha(_a){
    graph.set_instance(p);
}

void ConstructiveGraph::print_method_informations(){
    cout << "==========================================================================================" << endl;
    cout << " -> CONSTRUCTIVE GRAPH <- " << endl;    
}

Solution ConstructiveGraph::apply(){

    Graph graph(instance);
    graph = graph.construct_conjuctive_graph();

    // gera o sequenciamento das operações nas maquinas atraves de alguma regra de despacho
    // depois gera o grafo disjuntivo com base no sequenciamento gerado
    Grasp* dispatch_rule = new GraspPriority(instance, alpha);
    Solution initialSolution = dispatch_rule->apply();

    graph = graph.construct_disjuntive_graph(initialSolution.getSolution());

//    graph.bellmanFord();
//    graph.printCriticalPath();
//    graph.printEdges();

    initialSolution.setGraph(graph);

  /*   Evaluator eval(instance);
    cout << eval.evaluate_by_graph(initialSolution) << " "; 
*/

    initialSolution = dispatch_rule->refinement(initialSolution);

//    cout << eval.evaluate_by_graph(initialSolution) << endl;
    
    return initialSolution;
}

void ConstructiveGraph::print(){
    for(int i=0 ; i<graph.size() ; i++){
        std::cout << "(" << graph[i].source.job << "-" << graph[i].source.operation << ", " << 
        graph[i].destination.job << "-" << graph[i].destination.operation << ", " << 
        graph[i].weight << ")" << endl;
    }
}

void ConstructiveGraph::print_gantt(){
    
}
