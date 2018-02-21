#include "ShakeK.hpp"

ShakeK::ShakeK() : Metaheuristic(){
    k_moves = 1;
}

ShakeK::ShakeK(Solution s, int k) : Metaheuristic(s) {
    k_moves = k;
}

Solution ShakeK::apply(){

    vector<Edge> to_shake;

    auto criticalBlocks = graph.getCriticalBlocks();
    int tries = 0;
    int max_tries = sizeCriticalBlocks;

    while(to_shake.size() < (unsigned)k_moves && tries < max_tries){

        // aresta candidata a ser invertida
        Edge candidate;

        // escolhe bloco aleatorio
        int random_block = rand() % criticalBlocks.size();

        // escolhe entre uma aresta do inicio ou do fim do bloco critico
        int random_edge = rand() % criticalBlocks[random_block].size();
        candidate = criticalBlocks[random_block][random_edge];

        // verifica se a aresta candidata ja nao foi escolhida antes
        auto it = std::find(to_shake.begin(), to_shake.end(), candidate);
        if(it == to_shake.end()){
            to_shake.push_back(candidate);

            // verifica se as arestas escolhidas pertencem a blocos criticos diferentes
            sort(to_shake.begin(), to_shake.end());
            for(unsigned int i=0 ; i<criticalBlocks.size() && to_shake.size() > 1; i++){
                vector<Edge> c;
                sort(criticalBlocks[i].begin(), criticalBlocks[i].end());
                set_intersection(to_shake.begin(), to_shake.end(), criticalBlocks[i].begin(), criticalBlocks[i].end(), std::back_inserter(c));

                if(c.size() >= 2){
                    auto it = find(to_shake.begin(), to_shake.end(), candidate);
                    to_shake.erase(it);
                    tries++;
                    break;
                }
            }
            
        }
    }
    
    // inverte todas as arestas escolhidas
    for(Edge edge : to_shake){
        invert(edge);
    }

    if(!graph.isFeasible()){
        cout << "DEU MERDA PRA INVERTER" << endl;
        usleep(1000000);
    }
    
    solution.setGraph(graph);
    return solution;
}

void ShakeK::setKMoves(int k){
    k_moves = k;
}