#include "CEI.hpp"

CEI::CEI(Solution s) : Movement(s) {

}
    
CEI::CEI() : Movement(){

}

Solution CEI::apply(){

    updateCouldMove();
    printCouldMove();
    
    for(int i=0 ; i<couldMove.size() ; i++){
        if(couldMove[i].size() <= 2){
            couldMove.erase(couldMove.begin()+i);
        }
    }

    int random_block = rand() % couldMove.size();
    int choosed = ceil(couldMove[random_block].size()/2);

    cout << choosed << " " << couldMove[random_block].size() << endl;

    return solution;
}
/*
void CEI::updateCouldMove(){

    // atualiza o caminho critico e as arestas passiveis de troca
    criticalPath = graph.bellmanFord();

    couldMove.clear();
    graph.printCriticalPath();

    bool bloco = false;
    int blocoAtual = -1;
    for(int i=0 ; i<criticalPath.size() ; i++){

        for(int j=0 ; j<criticalPath[i].size()-1 ; j++){

            if(criticalPath[i][j].isCritical()){
                if(!bloco){
                    couldMove.push_back(vector<Edge>());
                    blocoAtual++;
                }
                couldMove[blocoAtual].push_back(criticalPath[i][j]);
                bloco = true;

            } else if(bloco == true) {
                bloco = false;
            }

        }

    }

    sort(couldMove.begin(), couldMove.end(), [&](const vector<Edge> a,
                                                        const vector<Edge> b){
        return a.size() > b.size();
    });

    cout << "ARESTAS QUE PODEM MOVER: " << endl;
    for(int i=0 ; i<couldMove.size() ; i++)
    {
        for(int j=0 ; j<couldMove[i].size() ; j++)
        {
            cout << "(" << couldMove[i][j].source.index << " " << couldMove[i][j].destination.index << "), ";
        }
        cout << endl;
    }

}

*/