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
    int index = 0;
    // constroi grafo conjuntivo - sequenciamento dos jobs
    while(jobAtual <= nJobs){
        Edge edge;

        edge.index = index;
        index++;

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

    // gera o sequenciamento das operações nas maquinas atravez de alguma regra de despacho
    // depois gera o grafo disjuntivo com base no sequenciamento anteriormente gerado
    Grasp grasp(instance, 0.5);
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

                edge.source = Node(source.job, source.task, vertexPerJob*source.job+source.task+1, NodeType::INTERNO);
                edge.destination = Node(dest.job, dest.task, vertexPerJob*dest.job+dest.task+1, NodeType::INTERNO);
                edge.weight = instance.get_vec_schedules(source.job, source.task).time_execution;

                graph.edges.push_back(edge);
            }
        }
    }

    cout << endl;
    this->print();

    vector<vector<Edge>> criticalPath = this->bellmanFord();
    vector<vector<Edge>> couldMove(nJobs);

    for(int i=0 ; i<nJobs ; i++)
    {
        if(criticalPath[i].size() > 1)
        {
            for(int j=0 ; j<criticalPath[i].size() ; j++)
            {
                if(criticalPath[i][j].source.job != criticalPath[i][j].destination.job && 
                    criticalPath[i][j].source.job != -1 && criticalPath[i][j].destination.job != -1)
                {
                    couldMove[i].push_back(criticalPath[i][j]);
                }
            }
        }
    }

//   this->print();

    cout << "ARESTAS QUE PODEM MOVER: " << endl;
    for(int i=0 ; i<couldMove.size() ; i++){
        cout << "Job " << i << ": ";
        for(int j=0 ; j<couldMove[i].size() ; j++){
            cout << "(" << couldMove[i][j].source.index << " " << couldMove[i][j].destination.index << "), ";
        }
        cout << endl;
    }

    graph.edges[couldMove[3][0].index].invertWay();
    graph.edges[couldMove[3][0].index].weight = instance.get_vec_schedules(couldMove[3][0].destination.job, couldMove[3][0].destination.operation).time_execution;

    //this->print();

////////////////////////////////////////////////////////////////////
/*
    criticalPath = bellmanFord();

     for(int i=0 ; i<nJobs ; i++)
    {
        couldMove[i].clear();
        if(criticalPath[i].size() > 1)
        {
            for(int j=0 ; j<criticalPath[i].size() ; j++)
            {
                if(criticalPath[i][j].source.job != criticalPath[i][j].destination.job && 
                    criticalPath[i][j].source.job != -1 && criticalPath[i][j].destination.job != -1)
                {
                    couldMove[i].push_back(criticalPath[i][j]);
                }
            }
        }
    }

//   this->print();

    cout << "ARESTAS QUE PODEM MOVER: " << endl;
    for(int i=0 ; i<couldMove.size() ; i++){
        cout << "Job " << i << ": ";
        for(int j=0 ; j<couldMove[i].size() ; j++){
            cout << "(" << couldMove[i][j].source.index << " " << couldMove[i][j].destination.index << "), ";
        }
        cout << endl;
    }

    graph.edges[couldMove[1][0].index].invertWay();
    graph.edges[couldMove[1][0].index].weight = instance.get_vec_schedules(couldMove[1][0].destination.job, couldMove[1][0].destination.operation).time_execution;

    cout << "DEPOIS MOVIMENTO: " << endl << endl;

    /////////////////////////////////////////////////////////////////////////

    criticalPath = bellmanFord();

     for(int i=0 ; i<nJobs ; i++)
    {
        couldMove[i].clear();
        if(criticalPath[i].size() > 1)
        {
            for(int j=0 ; j<criticalPath[i].size() ; j++)
            {
                if(criticalPath[i][j].source.job != criticalPath[i][j].destination.job && 
                    criticalPath[i][j].source.job != -1 && criticalPath[i][j].destination.job != -1)
                {
                    couldMove[i].push_back(criticalPath[i][j]);
                }
            }
        }
    }

//   this->print();

    cout << "ARESTAS QUE PODEM MOVER: " << endl;
    for(int i=0 ; i<couldMove.size() ; i++){
        cout << "Job " << i << ": ";
        for(int j=0 ; j<couldMove[i].size() ; j++){
            cout << "(" << couldMove[i][j].source.index << " " << couldMove[i][j].destination.index << "), ";
        }
        cout << endl;
    }

    /////////////////////////////////////////////////////////////////////////
*/
}   

vector<vector<Edge>> ConstructiveGraph::bellmanFord(){
    int nVertices = graph.nVertex;
    int nArestas = graph.edges.size();

	int dist[nVertices];

	// Step 1: Initialize distances from src to all other vertices as INFINITE
	for (int i = 0; i < nVertices; i++)
		dist[i] = -INF;

	dist[0] = 0;

    vector<Edge> caminhoEdge;
    caminhoEdge.resize(nVertices);

	// Step 2: Relax all edges |nVertices| - 1 times. A simple shortest 
	// path from src to any other vertex can have at-most |V| - 1 
	// edges
	for (int i = 1; i <= nVertices-1; i++)
	{
		for (int j = 0; j < nArestas; j++)
		{
            Node vertOrigem = (graph.edges[j].source);
            Node vertDestino = (graph.edges[j].destination);
			int weight = graph.edges[j].weight;
			if (dist[vertOrigem.index] != -INF && dist[vertOrigem.index] + weight > dist[vertDestino.index]){
                caminhoEdge[vertDestino.index] = graph.edges[j];
				dist[vertDestino.index] = dist[vertOrigem.index] + weight;
			}
		}
	}

    cout << "DISTANCES:" << endl;   
    printDistances(dist, nVertices);

    vector<vector<Edge>> criticalPath(instance.get_num_jobs());
    for(int job = 0 ; job < instance.get_num_jobs() ; job++){

        int i = (job+1)*vertexPerJob;
        while(i != 0)
        {
            criticalPath[job].push_back(caminhoEdge[i]);
            i = caminhoEdge[i].source.index;
        }
    }

    cout << "CAMINHO CRITICO:" << endl;
	for(int i=0 ; i<criticalPath.size() ; i++){
        cout << i << ": ";
        for(int j=0 ; j<criticalPath[i].size() ; j++){
            cout << "(" << criticalPath[i][j].source.index << " " << criticalPath[i][j].destination.index << "), ";
        }
        cout << endl;
	}

    return criticalPath;
}

void ConstructiveGraph::print(){
    for(int i=0 ; i<graph.edges.size() ; i++){
        std::cout << "(" << graph.edges[i].source.job << "-" << graph.edges[i].source.operation << ", " << 
        graph.edges[i].destination.job << "-" << graph.edges[i].destination.operation << ", " << 
        graph.edges[i].weight << ")" << endl;
    }
}

void ConstructiveGraph::printDistances(int dist[], int n){
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i, dist[i]);

}

void ConstructiveGraph::setInstance(ProblemInstance i){
    this->instance = i;
}