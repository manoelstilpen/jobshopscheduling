#ifndef METAHEURISTIC_HPP
#define METAHEURISTIC_HPP

#include "../Commons.hpp"
#include "../Solution.hpp"
#include "../Evaluator.hpp"

class Metaheuristic {

public:

    Metaheuristic(Solution sol){
        solution = sol;
        graph = sol.getGraph();
        instance = sol.getInstance();
        evaluator.set_instance(instance);
        timeTotal = 0;
        atrasoInicial = 0;
        melhorAtraso = 0;
        iterAtual = 0;
        iterTotal = 0;
        repeat=1;
    }

    Metaheuristic(){

    }

    virtual ~Metaheuristic(){

    }

    virtual Solution apply() = 0;

    virtual void updateCouldMove() {
        // atualiza o caminho critico e as arestas passiveis de troca

        criticalPath = graph.getCriticalPath();
        
        criticalBlocks.clear();
        sizeCriticalBlocks = 0;

        bool bloco = false;
        int blocoAtual = -1;
        for(int i=0 ; i<criticalPath.size() ; i++){

            if(isCritical(criticalPath[i])){
                if(!bloco){
                    criticalBlocks.push_back(vector<Edge>());
                    blocoAtual++;
                }

                criticalBlocks[blocoAtual].push_back(criticalPath[i]);
                bloco = true;

            } else if(bloco == true) {
                bloco = false;
            }

        }

        // ordena os blocos criticos em relacao a quantidade de arestas
        sort(criticalBlocks.begin(), criticalBlocks.end(), [&](const vector<Edge> a,
                                                            const vector<Edge> b){
            return a.size() > b.size();
        });


        // remove os blocos criticos repetidos
        for(int i=0 ; i<criticalBlocks.size() ; i++){
            int size = criticalBlocks[i].size();
            sizeCriticalBlocks += size;
            for(int j=i+1 ; j<criticalBlocks.size() && size == criticalBlocks[j].size() ; j++){
                if(std::equal(criticalBlocks[i].begin(), criticalBlocks[i].end(), criticalBlocks[j].begin())){
                    criticalBlocks.erase(criticalBlocks.begin()+j);
                    j--;
                }
            }

        }

    }

    bool isCritical(Edge edge){
        return (edge.first.job != edge.second.job) &&
                edge.first.job != -1 && edge.second.job != -1;
    }

    void invert(Edge edge){
        graph.invert(edge.first, edge.second);
        lastMovements.push_back(edge);
    }

    void undo_movements(){
        cout << "IMPLEMENTAR" << endl;
        /* for(int i=0 ; i<lastMovements.size() ; i++){
            graph.invert(lastMovements[i]);
        }

        lastMovements.clear(); */
    }

    void undo_last_movement(){
        graph.invert(lastMovements.back().second, lastMovements.back().first);
        lastMovements.pop_back();
    }

    void printCouldMove(){
        cout << "ARESTAS QUE PODEM MOVER: " << endl;
        for(int i=0 ; i<criticalBlocks.size() ; i++){
            for(int j=0 ; j<criticalBlocks[i].size() ; j++){
                cout << "(" << criticalBlocks[i][j].first.index << " " << criticalBlocks[i][j].second.index << "), ";
            }
            cout << endl;
        }
    }

    void print(){
        float perc = percent_between(atrasoInicial, melhorAtraso);
        cout << endl;
        cout << "ATRASO INICIAL: " << atrasoInicial << endl;
        cout << "ATRASO FINAL: " << melhorAtraso << " (" << perc << "%)" << endl;
        bestSolution.print_solution();
    }

    void print_graphic(){
        cout << atrasoInicial << "\t" << melhorAtraso << "\t" << timeTotal << endl;
    }

    void print_progress(){
        float progress = float(iterAtual)/float(iterTotal);
        int barWidth = 100;
        std::cout << "[";
        int pos = barWidth * progress;

        for (int i = 0; i < barWidth; i++) {
            if (i <= pos) std::cout << "\033[1;32m#\033[0m";
//            else if (i == pos) std::cout << "\033[1;31m>\033[0m";
            else std::cout << ".";
        }

        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();

//        std::cout << std::endl;
    }

    void print_method_informations(){
        cout << "==========================================================================================" << endl;
        cout << " -> METHOD <- " << endl;
    }

    void set_solution(Solution s){
        solution = s;
        set_graph(s.getGraph());
    }

    void set_graph(Graph g){
        graph = g;
    }

protected:
    Graph graph;
    Solution solution;
    Solution bestSolution;
    Evaluator evaluator;
    ProblemInstance instance;

    int atrasoInicial;
    int melhorAtraso;

    int iterAtual;
    int iterTotal;

    int repeat;
    int sizeCriticalBlocks;

    float timeTotal;

    vector<Edge> lastMovements;

    vector<Edge> criticalPath;
    vector< vector<Edge> > criticalBlocks;


};

#endif