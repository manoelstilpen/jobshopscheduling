#include "ConstructiveGraph.hpp"

ConstructiveGraph::ConstructiveGraph(){

}

ConstructiveGraph::ConstructiveGraph( double _a) : alpha(_a){
}

void ConstructiveGraph::print_method_informations(){
    cout << "==========================================================================================" << endl;
    cout << " -> CONSTRUCTIVE GRAPH <- " << endl;    
}

Solution ConstructiveGraph::apply(){

    Graph graph;
    graph = graph.construct_conjunctive_graph();

    // gera o sequenciamento das operações nas maquinas atraves de alguma regra de despacho
    // depois gera o grafo disjuntivo com base no sequenciamento gerado

    Constructive* constructive = new SPRT(alpha);
    Solution initialSolution = constructive->apply();

    graph = graph.construct_disjunctive_graph(initialSolution.getSolution()); 

    initialSolution.setGraph(graph);
//    constructive->print();
    
    return initialSolution;
}

void ConstructiveGraph::set_alpha(double _alpha){
    alpha = _alpha;
}