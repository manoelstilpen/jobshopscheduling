#include "ConstructiveGraph.hpp"

ConstructiveGraph::ConstructiveGraph(){

}

void ConstructiveGraph::construct(){
    ScheduleMatrix schedules = instance.get_vec_schedules();
    int nJobs = instance.get_num_jobs();
    int nOperations = instance.get_num_tasks();

    vertexPerJob = nOperations + GHOSTNODES;

    // quantidade de operacoes + nodos finais(2) + no inicial(1)
    graph.nVertex = (nOperations+GHOSTNODES)*nJobs + INITNODE;

    int jobAtual = 1;
    int vertexAtual = -1;
    // constroi grafo conjuntivo - sequenciamento dos jobs
    while(jobAtual <= nJobs){
        Edge edge;

        // final de um job
        if(vertexAtual == (vertexPerJob-1))
        {
            edge.source = Node(-1, -1, 0, NodeType::BEGIN);
            edge.destination = Node(jobAtual-1, vertexAtual%vertexPerJob, (vertexAtual+1)*(jobAtual), NodeType::GHOST);
            edge.weight = 0;

            jobAtual++;
            vertexAtual = -1;
        } 
        else 
        {
            if(vertexAtual == -1)
            { // inicio de um job, cria o node inicial
                edge.source = Node(-1, -1, 0, NodeType::BEGIN);
                edge.destination = Node(jobAtual-1, vertexAtual+1, (vertexPerJob)*(jobAtual-1)+1, NodeType::INTERNO);
                edge.weight = 0;
            }
            else
            {
                edge.source = Node(jobAtual-1, vertexAtual, (vertexPerJob)*(jobAtual-1)+vertexAtual+1, NodeType::INTERNO);
                edge.destination = Node(jobAtual-1, vertexAtual+1, (vertexPerJob)*(jobAtual-1)+vertexAtual+2, NodeType::INTERNO);
                if(vertexAtual < nOperations)
                {
                    // caso for um vertice pertencente a sequencia do job
                    edge.weight = schedules[jobAtual-1][vertexAtual].time_execution;
                }
                else 
                {
                    // caso for o vertice Bj
                    //edge.source = Node(jobAtual-1, -1, NodeType::GHOST);
                    //edge.destination = Node(jobAtual-1, -1, NodeType::GHOST);
                    edge.weight = -instance.get_due_times(jobAtual-1);
                }
            }
            vertexAtual++;
        }
        graph.edges.push_back(edge);
    }

//    this->print();

    Grasp grasp(instance, 0.5);
    Solution solution = grasp.apply_grasp2();

    this->bellmanFord();
}

void ConstructiveGraph::bellmanFord(){
    int nVertices = graph.nVertex;
    int nArestas = graph.edges.size();

	int dist[nVertices];

	// Step 1: Initialize distances from src to all other vertices as INFINITE
	for (int i = 0; i < nVertices; i++)
		dist[i] = -INF;

	dist[0] = 0;

	vector<int> caminho;
	caminho.resize(nVertices);

	// Step 2: Relax all edges |nVertices| - 1 times. A simple shortest 
	// path from src to any other vertex can have at-most |V| - 1 
	// edges
	for (int i = 1; i <= nVertices-1; i++)
	{
		for (int j = 0; j < nArestas; j++)
		{
            int vertOrigem = (graph.edges[j].source.index);
            int vertDestino = (graph.edges[j].destination.index);
			int weight = graph.edges[j].weight;
			if (dist[vertOrigem] != -INF && dist[vertOrigem] + weight > dist[vertDestino]){
				caminho[vertDestino] = (vertOrigem);
				dist[vertDestino] = dist[vertOrigem] + weight;
			}
		}
	}

	for(int i=0 ; i<caminho.size() ; i++){
		cout << i << ": " << caminho[i] << ", ";
	}
	cout << endl;
}

void ConstructiveGraph::print(){
    for(int i=0 ; i<graph.edges.size() ; i++){
        std::cout << "(" << graph.edges[i].source.job << "-" << graph.edges[i].source.operation << ", " << 
        graph.edges[i].destination.job << "-" << graph.edges[i].destination.operation << ", " << 
        graph.edges[i].weight << ")" << endl;
    }
}

void ConstructiveGraph::setInstance(ProblemInstance i){
    this->instance = i;
}