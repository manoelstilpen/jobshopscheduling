//
// Created by manoel on 14/03/18.
//

#include <GraphUtils/BellmanFord.hpp>

vector<Edge> BellmanFord::getCriticalPath(){
//
//    // Step 1: Initialize distances from src to all other vertices as -INFINITE
//    vector<int> distances(nVertex, -INF);
//    distances[0] = 0;
//
//    vector<int> path;
//    path.resize(nVertex);
//
//    // Step 2: Relax all edges |nVertex|-1 times. A simple longest
//    // path from src to any other vertex can have at-most |V| - 1 edges
//    bool houveAlteracao = true;
//    for (int i = 1; i <= nVertex-1 && houveAlteracao ; i++){
//        houveAlteracao = false;
//        for(unsigned int j=0 ; j<edges.size() ; j++){
//            for (unsigned int k = 0; k < edges[j].size(); k++){
//
//                int vertOrigem = j;
//                int vertDestino = edges[j][k].index;
//                int weight = edges[j][k].weight;
//
//                if (distances[vertOrigem] != -INF && distances[vertOrigem] + weight > distances[vertDestino]){
//                    path[vertDestino] = vertOrigem;
//                    distances[vertDestino] = distances[vertOrigem] + weight;
//                    houveAlteracao = true;
//                }
//
//            }
//        }
//    }
//
////    clock_t end = clock();
////    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
////    cout << elapsed_secs << endl;
//
//    /*  for (int i = 0; i < distances.size(); ++i)
//         printf("%d \t %d\n", i, distances[i]);
//      */
///*
//    cout << "CAMINHO" << endl;
//    for(int i=0 ; i<path.size(); i++){
//        cout << i << ": " << path[i] << endl;
//    }
//    cout << endl; */
//
//    vector<Edge> criticalPath;
//
//    for(int job = 0 ; job < instance.get_num_jobs() ; job++){
//
//        int i = (job+1)*vertexPerJob;
//        int tamanho = 0;
//
//        while(i != 0 && tamanho < nVertex-1){
//            criticalPath.push_back(make_pair(vertexList[path[i]], vertexList[i]));
//            i = path[i];
//            tamanho++;
//        }
//    }
//
//    return criticalPath;

}
