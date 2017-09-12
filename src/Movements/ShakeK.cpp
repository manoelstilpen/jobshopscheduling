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
        int choice = rand() % 2;

        if(choice == 0){
            invert(couldMove[random_block][0].index);
        } else if(choice == 1){
            invert(couldMove[random_block].back().index);
        } /*else if(choice == 2){
            invert(couldMove[random_block][0].index);
            invert(couldMove[random_block].back().index);

            if(!graph.isFeasible()){
                undo_last_movement();
                undo_last_movement();
            }
        }*/

        inicio = !inicio;
    }

    solution.setGraph(graph);
    return solution;
}

void ShakeK::setKMoves(int k){
    k_moves = k;
}