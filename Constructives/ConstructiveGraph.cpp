#include "ConstructiveGraph.hpp"

ConstructiveGraph::ConstructiveGraph() : Constructive(){

}

ConstructiveGraph::ConstructiveGraph(ProblemInstance p) : Constructive(p){
    graph.set_instance(p);
}

void ConstructiveGraph::print_method_informations(){
    cout << "==========================================================================================" << endl;
    cout << " -> CONSTRUCTIVE GRAPH <- " << endl;    
}

Solution ConstructiveGraph::apply(){

    Graph graph(instance);
    graph = graph.construct_conjuctive_graph();
    
//    this->print();

    // gera o sequenciamento das operações nas maquinas atravez de alguma regra de despacho
    // depois gera o grafo disjuntivo com base no sequenciamento anteriormente gerado
    GraspPriority grasp(instance, 0);
    Solution initialSolution = grasp.apply();
    grasp.print();

    graph = graph.construct_disjuntive_graph(initialSolution.getSolution());

    initialSolution.setGraph(graph);

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
