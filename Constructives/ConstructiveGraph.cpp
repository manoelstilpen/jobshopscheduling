#include "ConstructiveGraph.hpp"

ConstructiveGraph::ConstructiveGraph() : Constructive(){

}

ConstructiveGraph::ConstructiveGraph(ProblemInstance p) : Constructive(p){
    graph.setInstance(p);
}

Solution ConstructiveGraph::apply(){

    int jobAtual = 1;
    int vertexAtual = -1;
    int index = 0;
    // constroi grafo conjuntivo - sequenciamento dos jobs
    while(jobAtual <= nJobs){
        Edge edge;

        edge.index = index;
        edge.critical = false;
        index++;

        // final de um job
        if(vertexAtual == (graph.getVertexPerJob()-1))
        {
            edge.source = Node(-1, -1, 0, NodeType::BEGIN);
            edge.destination = Node(jobAtual-1, vertexAtual%graph.getVertexPerJob(), (vertexAtual+1)*(jobAtual), NodeType::GHOST);
            edge.weight = 0;

            jobAtual++;
            vertexAtual = -1;
        }
        else
        {
            if(vertexAtual == -1)
            { // inicio de um job, cria o node inicial
                edge.source = Node(-1, -1, 0, NodeType::BEGIN);
                edge.destination = Node(jobAtual-1, vertexAtual+1, (graph.getVertexPerJob())*(jobAtual-1)+1, NodeType::INTERNO);
                edge.weight = 0;
            }
            else
            {
                edge.source = Node(jobAtual-1, vertexAtual, (graph.getVertexPerJob())*(jobAtual-1)+vertexAtual+1, NodeType::INTERNO);
                edge.destination = Node(jobAtual-1, vertexAtual+1, (graph.getVertexPerJob())*(jobAtual-1)+vertexAtual+2, NodeType::INTERNO);
                if(vertexAtual < nOperations)
                {
                    // caso for um vertice pertencente a sequencia do job
                    edge.weight = instance[jobAtual-1][vertexAtual].time_execution;
                }
                else 
                {
                    // caso for o vertice Bj
                    edge.weight = -instance.get_due_times(jobAtual-1);
                }
            }
            vertexAtual++;
        }
        graph.add(edge);
    }

//    this->print();

    // gera o sequenciamento das operações nas maquinas atravez de alguma regra de despacho
    // depois gera o grafo disjuntivo com base no sequenciamento anteriormente gerado
    GraspSPRT grasp(instance, 0);
//    Solution initialSolution = grasp.apply_grasp2();
    Solution initialSolution = grasp.apply();
    grasp.print();

    // criando grafo disjuntivo atraves do sequenciamento gerado pelo grasp
    for(int i=0 ; i<initialSolution.size() ; i++)
    {
        for(int j=0 ; j<initialSolution[i].size() ; j++)
        {

            Schedule dest;
            Schedule source = initialSolution[i][j];

            for(int k=j+1 ; k<initialSolution[i].size() ; k++)
            {
                Edge edge;
                edge.index = index;
                index++; 

                dest = initialSolution[i][k];

                edge.critical = verify_critical(source, dest);

                edge.source = Node(source.job, source.task, graph.getVertexPerJob()*source.job+source.task+1, NodeType::INTERNO);
                edge.destination = Node(dest.job, dest.task, graph.getVertexPerJob()*dest.job+dest.task+1, NodeType::INTERNO);
                edge.weight = instance[source.job][source.task].time_execution;

                graph.add(edge);
            }
        }
    }

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
