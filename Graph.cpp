#include "Graph.hpp"

Graph::Graph(){

}

Graph::Graph(ProblemInstance p){
    setInstance(p);
}   

void Graph::add(Edge e){
    this->edges.push_back(e);
}

int Graph::size(){
    return this->edges.size();
}

void Graph::setInstance(ProblemInstance p){
    this->instance = p;
    this->vertexPerJob = p.get_num_tasks() + GHOSTNODES;
    this->nVertex = (p.get_num_tasks()+GHOSTNODES)*p.get_num_jobs() + INITNODE;
}

vector<vector<Edge>> Graph::bellmanFord(){
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
	for (int i = 1; i <= nVertex-1; i++)
	{
		for (int j = 0; j < nArestas; j++)
		{
            Node vertOrigem = (edges[j].source);
            Node vertDestino = (edges[j].destination);
			int weight = edges[j].weight;
			if (distances[vertOrigem.index] != -INF && distances[vertOrigem.index] + weight > distances[vertDestino.index]){
                caminhoEdge[vertDestino.index] = edges[j];
				distances[vertDestino.index] = distances[vertOrigem.index] + weight;
			}
		}
	}
/*
    cout << "DISTANCES:" << endl;   
    printDistances();
*/
    vector<vector<Edge>> criticalPath(instance.get_num_jobs());
    for(int job = 0 ; job < instance.get_num_jobs() ; job++){

        int i = (job+1)*vertexPerJob;
        while(i != 0)
        {
            criticalPath[job].push_back(caminhoEdge[i]);
            i = caminhoEdge[i].source.index;
        }
    }

/*    cout << "CAMINHO CRITICO:" << endl;
	for(int i=0 ; i<criticalPath.size() ; i++){
        cout << i << ": ";
        for(int j=0 ; j<criticalPath[i].size() ; j++){
            cout << "(" << criticalPath[i][j].source.index << " " << criticalPath[i][j].destination.index << "), ";
        }
        cout << endl;
	}
*/
    return criticalPath;
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

GanttRepresentation Graph::generate_gantt(){

    GanttRepresentation solution;
    solution.resize(instance.get_num_machines());

//    bellmanFord();
    
    // gera o grafico com base no grafo
    for(int i=0 ; i<instance.get_num_jobs() ; i++){
        for(int j=0 ; j<instance.get_num_operations() ; j++){
            Schedule atual = instance[i][j];
            solution[atual.machine].push_back(atual);
            solution[atual.machine].back().time_execution = getDistanceFrom(atual.job, atual.task) + instance[atual.job][atual.task].time_execution; 
        }
    }

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