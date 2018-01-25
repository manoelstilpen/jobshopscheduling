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

    Constructive* grasp = new ASPRT(instance, alpha);
    Solution initialSolution = grasp->apply();

    graph = graph.construct_disjunctive_graph(initialSolution.getSolution()); 

    initialSolution.setGraph(graph);
    initialSolution.print_solution();

    graph.getCriticalPath();
    for(int i=0 ; i<instance.get_num_jobs() ; i++){
        for(int j=0 ; j<instance.get_num_operations() ; j++){
            cout << graph.getDistanceFrom(i+1) << " ";
        }
        cout << endl;
    }

    return initialSolution;
}

void ConstructiveGraph::set_alpha(double _alpha){
    alpha = _alpha;
}