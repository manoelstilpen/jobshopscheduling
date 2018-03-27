//
// Created by manoel on 14/03/18.
//

#include <GraphUtils/BellmanFord.hpp>

BellmanFord::BellmanFord() : CriticalPath(){

}

vector<Edge> BellmanFord::getCriticalPath(map<int, vector<Node> >& graph, map<int, Node>& vertexList, vector<int>& distances){

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
        for(unsigned int j=0 ; j<graph.size() ; j++){
            for (unsigned int k = 0; k < graph[j].size(); k++){

                int vertOrigem = j;
                int vertDestino = graph[j][k].index;
                int weight = graph[j][k].weight;

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

    vector<Edge> criticalPath;

    for(int job = 0 ; job < ProblemInstance::getNumJobs() ; job++){

        int i = (job+1)*vertexPerJob;
        int tamanho = 0;

        while(i != 0 && tamanho < nVertex-1){
            criticalPath.emplace_back(make_pair(vertexList[path[i]], vertexList[i]));
            i = path[i];
            tamanho++;
        }
    }

    return criticalPath;

}
