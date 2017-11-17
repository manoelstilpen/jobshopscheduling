#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "../Commons.hpp"
#include "../Solution.hpp"
#include "../Evaluator.hpp"

class Movement{

public: 

    Movement(Solution sol){
        this->solution = sol;
        this->graph = sol.getGraph();
        this->instance = sol.getInstance();
        this->evaluator.set_instance(this->instance);

        this->timeTotal = 0;
        this->atrasoInicial = 0;
        this->melhorAtraso = 0;

        this->iterAtual = 0;
        this->iterTotal = 0;
    }

    Movement(){

    }

    virtual ~Movement(){
        
    }

    virtual Solution apply() = 0;

    virtual void updateCouldMove() {
        // atualiza o caminho critico e as arestas passiveis de troca
        criticalPath = graph.bellmanFord();

        criticalBlocks.clear();
        
        bool bloco = false;
        int blocoAtual = -1;
        for(int i=0 ; i<criticalPath.size() ; i++){

            if(isCritical(criticalPath[i])){
                if(!bloco){
                    criticalBlocks.push_back(vector<pair<Node, Node> >());
                    blocoAtual++;
                }

                criticalBlocks[blocoAtual].push_back(criticalPath[i]);
                bloco = true;

            } else if(bloco == true) {
                bloco = false;
            }

        }

        sort(criticalBlocks.begin(), criticalBlocks.end(), [&](const vector<pair<Node, Node>> a,
                                                            const vector<pair<Node, Node>> b){
            return a.size() > b.size();
        });

//        printCouldMove();
    }

    bool isCritical(pair<Node, Node> edge){
        return (edge.first.job != edge.second.job) && 
                edge.first.job != -1 && edge.second.job != -1;
    }

    void invert(pair<Node, Node> edge){
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

    float timeTotal;

    vector<pair<Node, Node> > lastMovements;

    vector< pair<Node, Node > > criticalPath;
    vector< vector< pair<Node, Node > > > criticalBlocks;


};

#endif