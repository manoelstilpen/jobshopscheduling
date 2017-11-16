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

void Graph::add(Node src, Node dest, EdgeData data){
    // adding edge
    edges[src.index].push_back(make_pair(dest, data));
    nEdges++;
}

void Graph::add(int src, int dest){
    //add edge by it's id

}

// TODO: inverter uma aresta recebendo os indices dos vertices como parametro
void Graph::invert(int src, int dest){
    cout << "IMPLEMENTAR" << endl;
}

void Graph::invert(Node src, Node dest){
    int idSrc = (vertexPerJob)*(src.job)+src.operation+1;
    int idDest = (vertexPerJob)*(dest.job)+dest.operation+1;
    
    // verifica se existe aresta entre src e dest
    auto it = std::find_if(edges[idSrc].begin(), edges[idSrc].end(), [&](const std::pair<Node, EdgeData>& n1){
        return n1.first.job == dest.job && n1.first.operation == dest.operation;
    });

    // nao existe aresta, retorna com erro
    if(it == edges[idSrc].end()){
        cout << "INVERSAO INVALIDA" << endl;
        return;
    }

    // invertendo
    edges[idSrc].erase(it);
    edges[idDest].push_back(make_pair(Node(src.job, src.operation, idSrc, NodeType::INTERNO), (*it).second));
}

vector< pair<Node, Node> > Graph::bellmanFord(){

    int nArestas = nEdges;

    // Step 1: Initialize distances from src to all other vertices as INFINITE
    distances.clear();
	distances.resize(nVertex, -INF);
    distances[0] = 0;
        
    vector<int> caminhoEdge;
    caminhoEdge.resize(nVertex);

	// Step 2: Relax all edges |nVertex|-1 times. A simple longest 
	// path from src to any other vertex can have at-most |V| - 1 
	// edges
	for (int i = 1; i <= nVertex-1; i++){
        for(int j=0 ; j<edges.size() ; j++){
		    for (int k = 0; k < edges[j].size(); k++){

                int vertOrigem = j;
                int vertDestino = (edges[j][k].first.index);
                int weight = edges[j][k].second.weight;

                if (distances[vertOrigem] != -INF && distances[vertOrigem] + weight > distances[vertDestino]){
                    caminhoEdge[vertDestino] = vertOrigem;
                    distances[vertDestino] = distances[vertOrigem] + weight;
                }

            }
        }
    }

    /* for (int i = 0; i < distances.size(); ++i)
        printf("%d \t %d\n", i, distances[i]);
    

    cout << "CAMINHO" << endl;
    for(int i=0 ; i<caminhoEdge.size(); i++){
        cout << i << ": " << caminhoEdge[i] << endl;
    }
    cout << endl; */

    vector< pair<Node, Node> > criticalPath;
    
    //if(isFeasible(distances)){

        for(int job = 0 ; job < instance.get_num_jobs() ; job++){

            int i = (job+1)*vertexPerJob;
            int tamanho = 0;

            while(i != 0 && tamanho < nVertex-1){   
                criticalPath.push_back(make_pair(vertexList[caminhoEdge[i]], vertexList[i]));
                i = caminhoEdge[i];
                tamanho++;
            }
        }

        /* cout << "CAMINHOS CRITICOS GRAFO: " << endl;
        for(int i=0 ; i<criticalPath.size() ; i++){
            cout << criticalPath[i].first.toString() << " " << criticalPath[i].second.toString() << endl;
        }
        cout << "END" << endl;  */

    return criticalPath;
}

// TODO
bool Graph::isFeasible(vector<int> distances){

    for(int i=0 ; i<edges.size() ; i++){
        for (int j = 0; j < edges[i].size(); j++){
            int u = i;
            int v = edges[i][j].first.index;
            int weight = edges[i][j].second.weight;

            if (distances[u] != -INF && distances[u] + weight > distances[v]){
                cout << u << " " << v << endl;
                cout << "CONTEM CICLO" << endl;
                return false;
            }
        }
    }

    return true;
}

Graph Graph::construct_conjuctive_graph(){
    
    int nJobs = instance.get_num_jobs();
    int nOperations = instance.get_num_operations();

    int jobAtual = 1;
    int vertexAtual = -1;

    // constroi grafo conjuntivo - sequenciamento dos jobs
    while(jobAtual <= nJobs){
        EdgeData data;
        Node source;
        Node destination;

//        edge.index = nEdges;
//        nEdges++;
        data.critical = false;

        // final de um job
        if(vertexAtual == (vertexPerJob-1))
        {
            source = Node(-1, -1, 0, NodeType::BEGIN);
            destination = Node(jobAtual-1, vertexAtual%vertexPerJob, (vertexAtual+1)*(jobAtual), NodeType::GHOST);
            data.weight = 0;

            jobAtual++;
            vertexAtual = -1;
        }
        else
        {
            if(vertexAtual == -1)
            { // inicio de um job, cria o node inicial
                source = Node(-1, -1, 0, NodeType::BEGIN);
                destination = Node(jobAtual-1, vertexAtual+1, (vertexPerJob)*(jobAtual-1)+1, NodeType::INTERNO);
                data.weight = 0;
            }
            else
            {
                source = Node(jobAtual-1, vertexAtual, (vertexPerJob)*(jobAtual-1)+vertexAtual+1, NodeType::INTERNO);
                destination = Node(jobAtual-1, vertexAtual+1, (vertexPerJob)*(jobAtual-1)+vertexAtual+2, NodeType::INTERNO);
                if(vertexAtual < nOperations)
                {
                    // caso for um vertice pertencente a sequencia do job
                    data.weight = instance[jobAtual-1][vertexAtual].time_execution;
                }
                else 
                {
                    // caso for o vertice Bj
                    data.weight = -instance.get_due_times(jobAtual-1);
                }
            }

            vertexAtual++;
        }

        add(source);
        add(destination);
        add(source, destination, data);
    }

/*
     for(auto m : edges){
        cout << m.first << " - ";
        for(auto i : m.second){
            cout << "(" << i.first.job << " " << i.first.operation << " " << i.second.weight << ") "; 
        }
        cout << endl;
    }

    for(auto i : vertexList){
        cout << "(" << i.first << " " << i.second.job << " " << i.second.operation << ")" << endl;
    } 
*/
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
                EdgeData data;
//                edge.index = nEdges;
//                nEdges++;

                dest = initialSolution[i][k];

                data.critical = verify_critical(source, dest);

                Node src = Node(source.job, source.operation, vertexPerJob*source.job+source.operation+1, NodeType::INTERNO);
                Node destination = Node(dest.job, dest.operation, vertexPerJob*dest.job+dest.task+1, NodeType::INTERNO);
                data.weight = instance[source.job][source.task].time_execution;
                
                add(src);
                add(destination);
                add(src, destination, data);
            }
        }
    } 

//    bellmanFord();

    /* for(auto m : edges){
        cout << m.first << " - ";
        for(auto i : m.second){
            cout << "(" << i.first.job << " " << i.first.operation << " " << i.second.weight << ") "; 
        }
        cout << endl;
    } */

    /* for(auto i : vertexList){
        cout << "(" << i.first << " " << i.second.job << " " << i.second.operation << ")" << endl;
    } */

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

void Graph::printGraph(){
    for(auto m : edges){
        cout << m.first << " - ";
        for(auto i : m.second){
            cout << "(" << i.first.job << " " << i.first.operation << " " << i.second.weight << ") "; 
        }
        cout << endl;
    }
}