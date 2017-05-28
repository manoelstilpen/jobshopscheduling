#include "Graph.hpp"

Graph::Graph(){

}

Graph::Graph(ProblemInstance p){
    set_instance(p);
}   

void Graph::add(Edge e){
    this->edges.push_back(e);
}

int Graph::size(){
    return this->edges.size();
}

void Graph::set_instance(ProblemInstance p){
    this->instance = p;
    this->vertexPerJob = p.get_num_tasks() + GHOSTNODES;
    this->nVertex = (p.get_num_tasks()+GHOSTNODES)*p.get_num_jobs() + INITNODE;
}

vector< vector<Edge> > Graph::bellmanFord(){
    int nArestas = edges.size();

	distances.resize(nVertex);

	// Step 1: Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < distances.size(); i++)
		distances[i] = -INF;

	distances[0] = 0;

    vector<Edge> caminhoEdge;
    caminhoEdge.resize(nVertex);

	// Step 2: Relax all edges |nVertex| - 1 times. A simple shortest 
	// path from src to any other vertex can have at-most |V| - 1 
	// edges
    bool houveAlteracao = false;
	for (int i = 1; i <= nVertex-1; i++)
	{
        houveAlteracao = false;
		for (int j = 0; j < nArestas; j++)
		{
            Node vertOrigem = (edges[j].source);
            Node vertDestino = (edges[j].destination);
			int weight = edges[j].weight;
			if (distances[vertOrigem.index] != -INF && distances[vertOrigem.index] + weight > distances[vertDestino.index]){
                caminhoEdge[vertDestino.index] = edges[j];
				distances[vertDestino.index] = distances[vertOrigem.index] + weight;
                houveAlteracao = true;
			}
		}
	}
/*
    cout << "DISTANCES:" << endl;   
    printDistances();
*/
    criticalPath.clear();
    criticalPath.resize(instance.get_num_jobs());
    for(int job = 0 ; job < instance.get_num_jobs() ; job++){

        int i = (job+1)*vertexPerJob;
        while(i != 0)
        {
            criticalPath[job].push_back(caminhoEdge[i]);
            i = caminhoEdge[i].source.index;
        }
    }

    return criticalPath;
}

void Graph::printCriticalPath(){
    cout << "CAMINHO CRITICO:" << endl;
	for(int i=0 ; i<criticalPath.size() ; i++){
        cout << i << ": ";
        for(int j=0 ; j<criticalPath[i].size() ; j++){
            cout << "(" << criticalPath[i][j].source.index << " " << criticalPath[i][j].destination.index << "), ";
        }
        cout << endl;
	}
}

void Graph::invert(int index){
    edges[index].invertWay();
    edges[index].weight = instance[edges[index].source.job][edges[index].source.operation].time_execution;
    bellmanFord();
}

void Graph::printDistances(){
	printf("Vertex Distance from Source\n");
    for (int i = 0; i < distances.size(); ++i)
		printf("%d \t\t %d\n", i, distances[i]);

}

Graph Graph::construct_conjuctive_graph(){

    int nJobs = instance.get_num_jobs();
    int nOperations = instance.get_num_operations();

    int jobAtual = 1;
    int vertexAtual = -1;

    // constroi grafo conjuntivo - sequenciamento dos jobs
    while(jobAtual <= nJobs){
        Edge edge;

        edge.index = nEdges;
        edge.critical = false;
        nEdges++;

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
        add(edge);
    }

    return *this;

}

Graph Graph::construct_disjuntive_graph(GanttRepresentation initialSolution){
    // criando grafo disjuntivo atraves do sequenciamento gerado pelo metodo construtivo
    for(int i=0 ; i<initialSolution.size() ; i++)
    {
        for(int j=0 ; j<initialSolution[i].size() ; j++)
        {

            Schedule dest;
            Schedule source = initialSolution[i][j];

            for(int k=j+1 ; k<initialSolution[i].size() ; k++)
            {
                Edge edge;
                edge.index = nEdges;
                nEdges++;

                dest = initialSolution[i][k];

                edge.critical = verify_critical(source, dest);

                edge.source = Node(source.job, source.task, vertexPerJob*source.job+source.task+1, NodeType::INTERNO);
                edge.destination = Node(dest.job, dest.task, vertexPerJob*dest.job+dest.task+1, NodeType::INTERNO);
                edge.weight = instance[source.job][source.task].time_execution;

               add(edge);
            }
        }
    }

    return *this;
}

Graph Graph::generate_graph(GanttRepresentation solution){

    

}

GanttRepresentation Graph::generate_gantt(){

    GanttRepresentation solution;
    solution.resize(instance.get_num_machines());
    
    // gera o grafico com base no grafo
    for(int i=0 ; i<instance.get_num_jobs() ; i++){
        for(int j=0 ; j<instance.get_num_operations() ; j++){
            Schedule atual = instance[i][j];
            solution[atual.machine].push_back(atual);
            solution[atual.machine].back().time_execution = getDistanceFrom(atual.job, atual.task) + instance[atual.job][atual.task].time_execution; 
        }
    }

    // ordena as operacoes
    for(int i=0 ; i<solution.size() ; i++){
        sort(solution[i].begin(), solution[i].end(),
            [](const Schedule &a, const Schedule &b) -> bool{ 
                return a.time_execution < b.time_execution; 
            }
        );
    }

    return solution;
}

int Graph::getDistanceFrom(int j, int op){
    return distances[(vertexPerJob*j + op + 1)];
}

void Graph::setNVertex(int n){
    this->nVertex = n;
}

int Graph::getVertexPerJob(){
    return this->vertexPerJob;
}

vector<int> Graph::getDistances(){
    return this->distances;
}