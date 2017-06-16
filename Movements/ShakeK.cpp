#include "ShakeK.hpp"

ShakeK::ShakeK() : Movement(){
    k_moves = 1;
}

ShakeK::ShakeK(Solution s, int k) : Movement(s){
    k_moves = k;
}

Solution ShakeK::apply(){

    for(int i=0 ; i<k_moves ; i++){
        
        updateCouldMove();

        if(couldMove.size() == 0) break;

        int random_edge = rand() % couldMove.size(); // choose random edge to shake
        graph.invert(couldMove[random_edge].index);

        lastMovements.push_back(random_edge);
    }

    solution.setGraph(graph);
    return solution;
}

void ShakeK::setKMoves(int k){
    k_moves = k;
}