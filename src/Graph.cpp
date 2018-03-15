#include "Graph.hpp"

Graph::Graph(){
    nEdges = 0;
    nVertex = (ProblemInstance::getNumOperations()+GHOSTNODES)*ProblemInstance::getNumJobs()+ INITNODE;
    vertexPerJob = ProblemInstance::getNumOperations() + GHOSTNODES;
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

bool Graph::invert(Node src, Node dest, bool store){

    int idSrc = src.index;
    int idDest = dest.index;

    // verifica se existe aresta entre src e dest
    auto it = std::find_if(edges[idSrc].begin(), edges[idSrc].end(), [&](const Node& n1){
        return n1.job == dest.job && n1.operation == dest.operation;
    });

    // nao existe aresta, retorna com erro
    if(it == edges[idSrc].end() || src.job == dest.job){
        cout << "INVERSAO INVALIDA" << endl;
        return false;
    }

    // invertendo
    edges[idSrc].erase(it);
    edges[idDest].push_back(src);

    if(store){
        lastMovements.emplace_back(Edge(src, dest));
    }

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

void Graph::updateDistancesFromTopOrder(std::stack<int> order){

    distances.clear();
    distances.resize(nVertex, -INF);
    distances[0] = 0;

    path.clear();
    path.resize(nVertex);

    // Process vertices in topological order
    while (!order.empty()){
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

vector<Edge> Graph::getCriticalPath(){

    criticalPath.clear();
    topologicalSort();

    for(int job = 0 ; job < ProblemInstance::getNumJobs() ; job++){

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

vector< vector<Edge> > Graph::getCriticalBlocks(){
// atualiza o caminho critico e as arestas passiveis de inversao
    getCriticalPath();

    criticalBlocks.clear();
//        sizeCriticalBlocks = 0;

    bool bloco = false;
    int blocoAtual = -1;
    for(Edge i : criticalPath){

        if(isCritical(i)){
            if(!bloco){
                criticalBlocks.emplace_back(vector<Edge>());
                blocoAtual++;
            }

            criticalBlocks[blocoAtual].push_back(i);
            bloco = true;

        } else if(bloco) {
            bloco = false;
        }

    }

    // ordena os blocos criticos com relacao a quantidade de arestas
    sort(criticalBlocks.begin(), criticalBlocks.end(), [&](const vector<Edge> a,
                                                        const vector<Edge> b){
        return a.size() > b.size();
    });


    // remove os blocos criticos repetidos
    for(unsigned int i=0 ; i<criticalBlocks.size() ; i++){
        unsigned long size = criticalBlocks[i].size();
        // sizeCriticalBlocks += size;
        for(unsigned int j=i+1 ; j<criticalBlocks.size() && size == criticalBlocks[j].size() ; j++){
            if(std::equal(criticalBlocks[i].begin(), criticalBlocks[i].end(), criticalBlocks[j].begin())){
                criticalBlocks.erase(criticalBlocks.begin()+j);
                j--;
            }
        }

    }

    return criticalBlocks;
}

void Graph::undo_last_movement(){
    invert(lastMovements.back().second, lastMovements.back().first, false);
    lastMovements.pop_back();
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

    int nJobs = ProblemInstance::getNumJobs();

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
            add(Node(jobAtual, opAtual, vertexAtual, -ProblemInstance::getDueTimeFromJob(jobAtual)));
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
            add(Node(jobAtual, opAtual, vertexAtual, ProblemInstance::getSchedule(jobAtual,opAtual).time_execution));
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
    for(unsigned int i=0 ; i<initialSolution.size() ; i++)
    {
        for(unsigned int j=0 ; j<initialSolution[i].size() ; j++)
        {

            Schedule dest;
            Schedule source = initialSolution[i][j];

            for(unsigned int k=j+1 ; k<initialSolution[i].size() ; k++)
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
    solution.resize((ulong)ProblemInstance::getNumMachines());

    // gera o grafico com base no grafo
    for(int i=0 ; i<ProblemInstance::getNumJobs(); i++){
        for(int j=0 ; j<ProblemInstance::getNumOperations(); j++){
            Schedule atual = ProblemInstance::getSchedule(i, j);
            solution[atual.machine].push_back(atual);
            solution[atual.machine].back().time_execution = getDistanceFrom(vertexPerJob*atual.job+atual.operation+1) + ProblemInstance::getSchedule(atual.job,atual.operation).time_execution;

        }
    }

    // ordena as operacoes
    for(unsigned int i=0 ; i<solution.size() ; i++){
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
    if((unsigned)id > distances.size()){
        cout << "OUT OF BOUNDS" << endl;
        return 0;
    }
    
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
    for(unsigned int i=0 ; i<criticalPath.size() ; i++){
        cout << "(" << criticalPath[i].first.toString() << " " << criticalPath[i].second.toString() << ") - ";
    }
    cout << endl;
}

void Graph::printCriticalBlock(){
    cout << "BLOCOS CRITICOS:" << endl;
    for(unsigned int i=0 ; i<criticalBlocks.size() ; i++){
        cout << "BLOCO CRITICO " << i << ": ";
        for(unsigned int j=0 ; j<criticalBlocks[i].size() ; j++){
            cout << "(" << criticalBlocks[i][j].first << " " << criticalBlocks[i][j].second << ") - ";
        }
        cout << endl;
    }
    cout << endl;
}

vector< Edge > Graph::bellmanFord(){


}