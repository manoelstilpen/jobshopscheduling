#include "ShakeK.hpp"

ShakeK::ShakeK() : Metaheuristic(){
    k_moves = 1;
}

ShakeK::ShakeK(Solution s, int k) : Metaheuristic(s) {
    k_moves = k;
}

Solution ShakeK::apply(){

    updateCouldMove();
//    printCouldMove();
    vector<Edge> to_shake;

    int tries = 0;
    int max_tries = sizeCriticalBlocks;

    while(to_shake.size() < k_moves && tries < max_tries){

        // aresta candidata a ser invertida
        Edge candidate;

        // escolhe bloco aleatorio
        int random_block = rand() % criticalBlocks.size();
        // escolhe entre uma aresta do inicio ou do fim do bloco critico
        short int choice = rand() % 2;
        if(choice == 0){
            candidate = criticalBlocks[random_block][0];
        } else if(choice == 1){
            candidate = criticalBlocks[random_block].back();
        }
        // verifica se a aresta candidata ja nao foi escolhida antes
        auto it = std::find(to_shake.begin(), to_shake.end(), candidate);
        if(it == to_shake.end()){
            to_shake.push_back(candidate);

            for(int i=0 ; i<criticalBlocks.size() && to_shake.size() > 1; i++){
                vector<Edge> c;
                sort(to_shake.begin(), to_shake.end());
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

    if(k_moves != to_shake.size()) cout << k_moves << " movido: " << to_shake.size() << endl;

    solution.setGraph(graph);
    return solution;

    /*  else if(choice == 2){
            cout << "INVERTE DOIS " << random_block << endl;
            invert(criticalBlocks[random_block][0]);
            invert(criticalBlocks[random_block].back());

            if(!graph.isFeasible()){
                undo_last_movement();
                undo_last_movement();
                cout << "NAO PORRA" << endl;
            }
        } */
}

void ShakeK::setKMoves(int k){
    k_moves = k;
}