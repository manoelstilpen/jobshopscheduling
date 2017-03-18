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

    Grasp grasp(instance, 0.5);
    Solution initialSolution = grasp.apply_grasp2();

    for(int i=0 ; i<instance.get_num_machines() ; i++)
    {
        for(int j=0 ; j<initialSolution[i].size() ; j++)
        {
            Edge edge;
            edge.index = index;
            index++;

            Schedule source;
            Schedule dest;

            if(j == initialSolution[i].size()-1)
            {
                source = initialSolution[i][0];
                dest = initialSolution[i][j];
            }
            else
            {
                source = initialSolution[i][j];
                dest = initialSolution[i][j+1];
            }

            edge.source = Node(source.job, source.task, vertexPerJob*source.job+source.task+1, NodeType::INTERNO);
            edge.destination = Node(dest.job, dest.task, vertexPerJob*dest.job+dest.task+1, NodeType::INTERNO);
            edge.weight = instance.get_vec_schedules(source.job, source.task).time_execution;

            graph.edges.push_back(edge);
        }
    }

    //cout << endl;
    //this->print();

    vector<vector<Edge>> couldMove(nJobs);
    for(int i=0 ; i<nJobs ; i++)
    {
        vector<Edge> criticalPath = this->bellmanFord(i);

        if(criticalPath.size() > 1)
        {
            for(int j=0 ; j<criticalPath.size() ; j++)
            {
                if(criticalPath[j].source.job != criticalPath[j].destination.job && 
                    criticalPath[j].source.job != -1 && criticalPath[j].destination.job != -1)
                {
                    couldMove[i].push_back(criticalPath[j]);
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

/*    graph.edges[couldMove[0].index].invertWay();
    graph.edges[couldMove[0].index].weight = instance.get_vec_schedules(couldMove[0].destination.job, couldMove[0].destination.operation).time_execution;

    cout << "DEPOIS MOVIMENTO: " << endl << endl;
//    this->print();

    for(int i=0 ; i<3 ; i++){
        bellmanFord(i);
    }*/

}   

vector<Edge> ConstructiveGraph::bellmanFord(int job){
    int nVertices = graph.nVertex;
    int nArestas = graph.edges.size();

	int dist[nVertices];

	// Step 1: Initialize distances from src to all other vertices as INFINITE
	for (int i = 0; i < nVertices; i++)
		dist[i] = -INF;

	dist[0] = 0;

	vector<Node> caminho;
	caminho.resize(nVertices);

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
				caminho[vertDestino.index] = (vertOrigem);
                caminhoEdge[vertDestino.index] = graph.edges[j];
				dist[vertDestino.index] = dist[vertOrigem.index] + weight;
			}
		}
	}

 //   printDistances(dist, nVertices);

    vector<Edge> criticalPath;
    int i = (job+1)*vertexPerJob;
    while(i != 0)
    {
        criticalPath.push_back(caminhoEdge[i]);
        i = caminhoEdge[i].source.index;
    }

	for(int i=0 ; i<criticalPath.size() ; i++){
		cout << i << ": (" << criticalPath[i].source.index << " " << criticalPath[i].destination.index << "), ";
	}
	cout << endl;

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