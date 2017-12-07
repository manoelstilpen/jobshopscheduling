#include "Graph.hpp"

Graph::Graph(){
    nEdges = 0;
}

Graph::Graph(ProblemInstance p){
    nEdges = 0;
    set_instance(p);
}

void Graph::set_instance(ProblemInstance p){
    instance = p;
    vertexPerJob = p.get_num_tasks() + GHOSTNODES;
    nVertex = (p.get_num_tasks()+GHOSTNODES)*p.get_num_jobs() + INITNODE;
}

void Graph::add(Node node){
    // adding vertex
    vertexList[node.index] = node;
    nVertex = vertexList.size();
}

void Graph::add(Node src, Node dest){
    // adding edge
    edges[src.index].push_back(dest);
    nEdges++;
}

void Graph::add(int src, int dest){
    //add edge by it's id
}

// TODO: inverter uma aresta recebendo os indices dos vertices como parametro
bool Graph::invert(int src, int dest){
    cout << "IMPLEMENTAR" << endl;
}

bool Graph::invert(Node src, Node dest){
    /* int idSrc = getVertexId(src);
    int idDest = getVertexId(dest); */

    int idSrc = src.index;
    int idDest = dest.index;

    // verifica se existe aresta entre src e dest
    auto it = std::find_if(edges[idSrc].begin(), edges[idSrc].end(), [&](const Node& n1){
        return n1.job == dest.job && n1.operation == dest.operation;
    });

    // nao existe aresta, retorna com erro
    if(it == edges[idSrc].end()){
        cout << "INVERSAO INVALIDA" << endl;
        return false;
    } else if(src.job == dest.job){
        cout << "INVERSAO INVALIDA" << endl;
        return false;
    }

    // invertendo
    edges[idSrc].erase(it);
    edges[idDest].push_back(src);

    return true;
}
 
vector<int> Graph::topologicalSort(){
    stack<int> stack;

    vector<bool> visited(nVertex, false);
    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < nVertex; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, stack);

    updateDistancesFromTopOrder(stack);

    return stack_to_vector(stack);
}

void Graph::topologicalSortUtil(int v, vector<bool>& visited, stack<int>& stack){
    // Mark the current node as visited.
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    for (Node i: edges[v])
        if (!visited[i.index])
            topologicalSortUtil(i.index, visited, stack);
 
    // Push current vertex to stack which stores result
    stack.push(v);
}

void Graph::updateDistancesFromTopOrder(stack<int> order){

    distances.clear();
    distances.resize(nVertex, -INF);
    distances[0] = 0;

    path.clear();
    path.resize(nVertex);

    // Process vertices in topological order
    while (order.empty() == false){
        // Get the next vertex from topological order
        int u = order.top();
        order.pop();
 
        // Update distances of all adjacent vertices
        if (distances[u] != -INF){
            for (Node i: edges[u]){
                if (distances[i.index] < distances[u] + vertexList[u].weight){
                    distances[i.index] = distances[u] + vertexList[u].weight;
                    path[i.index] = u;
                }
            }
        }
    }
}

vector< pair<Node, Node> > Graph::getCriticalPath(){

    topologicalSort();

    criticalPath.clear();
    for(int job = 0 ; job < instance.get_num_jobs() ; job++){

        int i = (job+1)*vertexPerJob;
        int tamanho = 0;

        while(i != 0 && tamanho < nVertex-1){
            criticalPath.push_back(make_pair(vertexList[path[i]], vertexList[i]));
            i = path[i];
            tamanho++;
        }
    }
 
    //for (int i = 0; i < distances.size(); ++i)
    //    printf("%d \t %d\n", i, distances[i]);
    
    return criticalPath;
}

// DFS
bool Graph::isFeasible(){
    // marca todos os vertices como nao visitados e nao participantes da pilha de recursao
    vector<bool> visited(nVertex, false);
    vector<bool> recstack(nVertex, false);

    for(int i = 0; i < nVertex; i++)
        if (isFeasibleRec(vertexList[i], visited, recstack))
            return false;

    return true;
}

bool Graph::isFeasibleRec(Node v, vector<bool>& visited, vector<bool>& recstack)
{
    if(visited[v.index] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[v.index] = true;
        recstack[v.index] = true;

        // Recur for all the vertices adjacent to this vertex
        for(auto it : edges[v.index])
        {
            if ( !visited[it.index] && isFeasibleRec(it, visited, recstack) )
                return true;
            else if (recstack[it.index])
                return true;
        }

    }

    recstack[v.index] = false;  // remove the vertex from recursion stack

    return false;
}

Graph Graph::construct_conjunctive_graph(){

    int nJobs = instance.get_num_jobs();
    int nOperations = instance.get_num_operations();

    int jobAtual = 0;
    int opAtual = 0;
    int vertexAtual = 0;

    // armazenando as informacoes de cada vertice
    while(vertexAtual < vertexPerJob*nJobs+1)
    {
        if(vertexAtual == 0)
        {
            // vertice 0
            add(Node(-1, -1, 0, 0));
        }
        else if(opAtual == vertexPerJob-2)
        {
            // vertice Bj
            add(Node(jobAtual, opAtual, vertexAtual, -instance.get_due_times(jobAtual)));
            opAtual++;
        }
        else if(opAtual == vertexPerJob-1)
        {
            // vertice final do job
            add(Node(jobAtual, opAtual, vertexAtual, 0));
            opAtual = 0;
            jobAtual++;
        }
        else
        {
            // vertice intermediario - pertencente ao job
            add(Node(jobAtual, opAtual, vertexAtual, instance[jobAtual][opAtual].time_execution));
            opAtual++;
        }

        vertexAtual++;
    }

    jobAtual = 0;
    opAtual = -1;
    vertexAtual = 0;

    // define grafo conjuntivo - sequenciamento dos jobs
    while(jobAtual < nJobs)
    {
        Node source;
        Node destination;

        if(opAtual == -1)
        {
            // adiciona aresta entre vertice inicial e operacao 0
            source = vertexList[0];
            destination = vertexList[getVertexId(jobAtual, opAtual+1)];
            add(source, destination);

            destination = vertexList[getVertexId(jobAtual, vertexPerJob-1)];
            opAtual++;
        }
        else if (opAtual == vertexPerJob-2)
        {
            // adiciona aresta Bj para Fj
            source = vertexList[getVertexId(jobAtual, opAtual)];
            destination = vertexList[getVertexId(jobAtual, opAtual+1)];
            jobAtual++;
            opAtual = -1;
        }
        else
        {
            // adiciona aresta entre operacoes do job
            source = vertexList[getVertexId(jobAtual, opAtual)];
            destination = vertexList[getVertexId(jobAtual, opAtual+1)];
            opAtual++;
        }

        add(source, destination);
    }

    /* printGraph();

    for(auto i : vertexList){
        cout << "(" << i.first << " " << i.second.job << " " << i.second.operation << " " << i.second.weight << ")" << endl;
    }  */

    return *this;
}

Graph Graph::construct_disjunctive_graph(GanttRepresentation initialSolution){

    // criando grafo disjuntivo atraves do sequenciamento gerado pelo metodo construtivo
    for(int i=0 ; i<initialSolution.size() ; i++)
    {
        for(int j=0 ; j<initialSolution[i].size() ; j++)
        {

            Schedule dest;
            Schedule source = initialSolution[i][j];

            for(int k=j+1 ; k<initialSolution[i].size() ; k++)
            {
                dest = initialSolution[i][k];

                Node src = vertexList[getVertexId(source.job, source.operation)];
                Node destination = vertexList[getVertexId(dest.job, dest.operation)];

                add(src, destination);
            }
        }
    }  

    //printGraph();

    return *this;
}

GanttRepresentation Graph::generate_gantt(){

    GanttRepresentation solution;
    solution.resize(instance.get_num_machines());

    // gera o grafico com base no grafo
    for(int i=0 ; i<instance.get_num_jobs() ; i++){
        for(int j=0 ; j<instance.get_num_operations() ; j++){
            Schedule atual = instance[i][j];
            solution[atual.machine].push_back(atual);
            solution[atual.machine].back().time_execution = getDistanceFrom(vertexPerJob*atual.job+atual.operation+1) + instance[atual.job][atual.operation].time_execution;

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

int Graph::getNEdges(){
    int cont = 0;

    for(auto it = edges.begin() ; it != edges.end() ; it++){
        cont += it->second.size();
    }

    return cont;
}

int Graph::getVertexPerJob(){
    return vertexPerJob;
}

int Graph::getDistanceFrom(int id){
    return distances[id];
}

int Graph::getWeight(int job, int op){
    return vertexList[getVertexId(job,op)].weight;
}

int Graph::getVertexId(int job, int op){
    return vertexPerJob*job + op + 1;
}

int Graph::getVertexId(Node n){
    return getVertexId(n.job, n.operation);
}

Node Graph::getVertex(int id){
    return vertexList[id];
}

Node Graph::getVertex(int job, int op){
    return vertexList[getVertexId(job, op)];
}

map<int, vector<Node > > Graph::getAdjacencyList(){
    return edges;
}

void Graph::printGraph(){
    for(auto m : edges){
        cout << m.first << " - ";
        for(auto i : m.second){
            cout << "(" << i.job << " " << i.operation << " " << i.index << " " << i.weight << ") ";
        }
        cout << endl;
    }
}

void Graph::printCriticalPath(){
    cout << "TODO" << endl;
}

vector< pair<Node, Node> > Graph::bellmanFord(){

    // Step 1: Initialize distances from src to all other vertices as -INFINITE
    distances.clear();
    distances.resize(nVertex, -INF);
    distances[0] = 0;

    vector<int> path;
    path.resize(nVertex);

	// Step 2: Relax all edges |nVertex|-1 times. A simple longest
	// path from src to any other vertex can have at-most |V| - 1 edges
    bool houveAlteracao = true;
	for (int i = 1; i <= nVertex-1 && houveAlteracao ; i++){
        houveAlteracao = false;
        for(int j=0 ; j<edges.size() ; j++){
		    for (int k = 0; k < edges[j].size(); k++){

                int vertOrigem = j;
                int vertDestino = edges[j][k].index;
                int weight = edges[j][k].weight;
          
                if (distances[vertOrigem] != -INF && distances[vertOrigem] + weight > distances[vertDestino]){
                    path[vertDestino] = vertOrigem;
                    distances[vertDestino] = distances[vertOrigem] + weight;
                    houveAlteracao = true;
                }

            }
        }
    }

//    clock_t end = clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//    cout << elapsed_secs << endl;

   /*  for (int i = 0; i < distances.size(); ++i)
        printf("%d \t %d\n", i, distances[i]);
     */
/*
    cout << "CAMINHO" << endl;
    for(int i=0 ; i<path.size(); i++){
        cout << i << ": " << path[i] << endl;
    }
    cout << endl; */

    vector< pair<Node, Node> > criticalPath;

    for(int job = 0 ; job < instance.get_num_jobs() ; job++){

        int i = (job+1)*vertexPerJob;
        int tamanho = 0;

        while(i != 0 && tamanho < nVertex-1){
            criticalPath.push_back(make_pair(vertexList[path[i]], vertexList[i]));
            i = path[i];
            tamanho++;
        }
    }

    return criticalPath;
}