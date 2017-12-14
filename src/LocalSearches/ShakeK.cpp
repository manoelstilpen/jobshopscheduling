#include "ShakeK.hpp"

ShakeK::ShakeK() : Metaheuristic(){
    k_moves = 1;
}

ShakeK::ShakeK(Solution s, int k) : Metaheuristic(s){
    k_moves = k;
}

Solution ShakeK::apply(){

    //printCouldMove();
    
    for(int i=0 ; i<k_moves ; i++){
        
        updateCouldMove();
        //printCouldMove();

        if(criticalBlocks.size() == 0) break;

        int random_block = rand() % criticalBlocks.size(); // choose random block to shake

        /* int choice = [&](){
            if(criticalBlocks[random_block].size() > 2){
                return rand() % 3;
            } 

            return rand() % 2;
        }(); */

        int choice = rand() % 2;

        if(choice == 0){
            invert(criticalBlocks[random_block][0]);
            //cout << "inverteu " << criticalBlocks[random_block][0].first.index << " " << criticalBlocks[random_block][0].second.index << endl;
        } else if(choice == 1){
            invert(criticalBlocks[random_block].back());
            //cout << "inverteu " << criticalBlocks[random_block].back().first.index << " " << criticalBlocks[random_block].back().second.index << endl;
        } /* else if(choice == 2){
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

    solution.setGraph(graph);
    return solution;
}

void ShakeK::setKMoves(int k){
    k_moves = k;
}