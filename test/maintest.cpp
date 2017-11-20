#include "../src/Commons.hpp"
#include "../src/Graph.hpp"
#include "../src/Constructives/ConstructiveGraph.hpp"

#include <iostream>
#include <assert.h>

using namespace std;
using namespace twtjssp;

ProblemInstance instance;

bool unit_grafo_inversao(){

    ConstructiveGraph constructive(instance, 0);
	Solution s = constructive.apply();
    Graph graph = s.getGraph();
    
    // testando inversao de aresta
    Node src = graph.getVertex(3);
    Node dest = graph.getVertex(4);
    // nao pode ocorrer pois e uma aresta conjuntiva
    assert(graph.invert(src, dest) == false);
    
    src = graph.getVertex(11);
    dest = graph.getVertex(2);
    // nao pode ocorrer pois nao existe aresta entre src e dest
    assert(graph.invert(src,dest) == false);

    src = graph.getVertex(1,0);  // job 1 op 0 - vertice 6
    dest = graph.getVertex(0,2); // job 0 op 2 - vertice 3
    // inversao pode ocorrer pois e uma aresta disjuntiva
    assert(graph.invert(src,dest) == true);

    // verificacao do estado do grafo apos a inversao
    map<int, vector<Node> > adjacencyList = graph.getAdjacencyList();

    Node aux = adjacencyList[6].back();
    // dest não pode estar na lista do vertice 6, uma vez que ocorreu a inversao
    assert(aux != dest);

    aux = adjacencyList[3].back();
    // src precisa estar no final da lista do vertice 3, uma vez que a inversao ocorreu
    assert(aux == src);

    return true;
}

int main(){

	instance.set_name_file("Instances/bierwirth.txt");
	if(!instance.load_instance()){
		exit(EXIT_FAILURE);
	}

    unit_grafo_inversao();

}