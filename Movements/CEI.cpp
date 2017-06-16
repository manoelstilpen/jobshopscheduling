#include "CEI.hpp"

CEI::CEI(Solution s) : Movement(s) {

}
    
CEI::CEI() : Movement(){

}

Solution CEI::apply(){

    updateCouldMove();

    return solution;
}

void CEI::updateCouldMove(){

    // atualiza o caminho critico e as arestas passiveis de troca
    criticalPath = graph.bellmanFord();

    couldMove.clear();
    graph.printCriticalPath();

/*    sort(criticalPath.begin(), criticalPath.end(), [&](const vector<Edge> a,
                                                        const vector<Edge> b){
        return a.size() > b.size();
    });
*/
    bool bloco = false;
    for(int i=0 ; i<criticalPath.size() ; i++){

        for(int j=0 ; j<criticalPath[i].size()-1 ; j++){

            

        }

    }

}