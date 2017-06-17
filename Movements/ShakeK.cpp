#include "ShakeK.hpp"

ShakeK::ShakeK() : Movement(){
    k_moves = 1;
}

ShakeK::ShakeK(Solution s, int k) : Movement(s){
    k_moves = k;
}

Solution ShakeK::apply(){
    bool inicio = true;

    for(int i=0 ; i<k_moves ; i++){
        updateCouldMove();
        if(couldMove.size() == 0) break;

        int random_block = rand() % couldMove.size(); // choose random block to shake
        int random_edge = rand() % couldMove[random_block].size();
        
        if(inicio) invert(couldMove[random_block][0].index);
        else invert(couldMove[random_block].back().index);

        inicio = !inicio;

    }
    solution.setGraph(graph);
    return solution;
}

void ShakeK::setKMoves(int k){
    k_moves = k;
}