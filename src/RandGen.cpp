//
// Created by manoel on 26/03/18.
//

#include <RandGen.hpp>

long RandGen::seed = -1;

void RandGen::setSeed(long s){
    seed = s;
    srand(seed);
}

int RandGen::randomInt(int x){

    if(seed == -1) {
        cout << "You should define a random seed" << endl;
        return -1;
    }

    return (rand() % x);
}

void RandGen::printSeed(){
    cout << "Seed: " << seed << endl;
}