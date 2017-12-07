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

        if(criticalBlocks.size() == 0) break;

        int random_block = rand() % criticalBlocks.size(); // choose random block to shake
        int random_edge = rand() % criticalBlocks[random_block].size();
        int choice = rand() % 2;

        if(choice == 0){
            invert(criticalBlocks[random_block][0]);
        } else if(choice == 1){
            invert(criticalBlocks[random_block].back());
        } /*else if(choice == 2){
            invert(couldMove[random_block][0].index);
            invert(couldMove[random_block].back().index);

            if(!graph.isFeasible()){
                undo_last_movement();
                undo_last_movement();
            }
        }*/
    }

    solution.setGraph(graph);
    return solution;
}

void ShakeK::setKMoves(int k){
    k_moves = k;
}