#include "ConstructiveGraph.hpp"

ConstructiveGraph::ConstructiveGraph(){

}

ConstructiveGraph::ConstructiveGraph(ProblemInstance p, double _a) : alpha(_a), instance(p){
    graph.set_instance(p);
}

void ConstructiveGraph::print_method_informations(){
    cout << "==========================================================================================" << endl;
    cout << " -> CONSTRUCTIVE GRAPH <- " << endl;    
}

Solution ConstructiveGraph::apply(){

    Graph graph(instance);
    graph = graph.construct_conjunctive_graph();

    // gera o sequenciamento das operações nas maquinas atraves de alguma regra de despacho
    // depois gera o grafo disjuntivo com base no sequenciamento gerado

    // priority rule
    Constructive* grasp = new ASPRT(instance, alpha);
    Solution initialSolution = grasp->apply();

    graph = graph.construct_disjunctive_graph(initialSolution.getSolution()); 

    initialSolution.setGraph(graph);

//    Evaluator eval(instance);
//    cout << eval.evaluate_by_graph(initialSolution) << " ";

//    cout << eval.evaluate_by_graph(initialSolution) << endl;

    return initialSolution;
}

void ConstructiveGraph::setAlpha(double _alpha){
    alpha = _alpha;
}

void ConstructiveGraph::print(){
   
}

void ConstructiveGraph::print_gantt(){
    
}
