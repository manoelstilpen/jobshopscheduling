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
    }

    Movement(){

    }

    virtual ~Movement(){
        
    }

    virtual Solution apply() = 0;

    virtual void updateCouldMove() {

        // atualiza o caminho critico e as arestas passiveis de troca
        criticalPath = graph.bellmanFord();

        couldMove.clear();
//        graph.printCriticalPath();
        // apenas move as arestas que estao ou no inicio do caminho ou no fim
        for(int i=0 ; i<criticalPath.size() ; i++)
        {
            int size = criticalPath[i].size();

            if(size > 1)
            {
                for(int j=0 ; j<criticalPath[i].size() ; j++)
                {
                    if(criticalPath[i][j].isCritical())
                    {
                        if(std::find_if(couldMove.begin(), couldMove.end(), [&](const Edge& a){
                                return a.source.job == criticalPath[i][j].source.job &&
                                        a.destination.job == criticalPath[i][j].destination.job &&
                                        a.source.operation == criticalPath[i][j].source.operation &&
                                        a.destination.operation == criticalPath[i][j].destination.operation; 
                            
                            }) == couldMove.end()) {

                                // v does not contains x 
                                couldMove.push_back(criticalPath[i][j]);
                        } 
                    }
                }
                    /*while(j < size-2 && criticalPath[i][j].isCritical() && criticalPath[i][j+1].isCritical())
                    {
                        cout << criticalPath[i][j].source.index << " " << criticalPath[i][j].destination.index
                         << ") " << criticalPath[i][j+1].source.index << " " << criticalPath[i][j+1].destination.index << endl;
                        if(std::find_if(couldMove.begin(), couldMove.end(), [&](const Edge& a){
                                return a.source.job == criticalPath[i][j].source.job &&
                                        a.destination.job == criticalPath[i][j].destination.job &&
                                        a.source.operation == criticalPath[i][j].source.operation &&
                                        a.destination.operation == criticalPath[i][j].destination.operation; 
                            
                            }) == couldMove.end()) {

                                // v does not contains x 
                                couldMove.push_back(criticalPath[i][j]);
  //                              cout << "NAO CONTEM PRIMEIRO" << endl;
                        } 
                        
                        if (std::find_if(couldMove.begin(), couldMove.end(), [&](const Edge& a){
                                return a.source.job == criticalPath[i][j+1].source.job &&
                                        a.destination.job == criticalPath[i][j+1].destination.job &&
                                        a.source.operation == criticalPath[i][j+1].source.operation &&
                                        a.destination.operation == criticalPath[i][j+1].destination.operation; 
                            
                            }) == couldMove.end())
                        {                        
                                couldMove.push_back(criticalPath[i][j+1]);
    //                            cout << "NAO CONTEM SEGUNDO" << endl;
                        }

                        j += 1; 
                    }

                }*/

            }
        }

//        printCouldMove();
    }

    void undo_movements(){

        for(int i=0 ; i<lastMovements.size() ; i++){
            graph.invert(lastMovements[i]);
        }

        lastMovements.clear();
    }

    void undo_last_movement(){
        graph.invert(lastMovements.back());
        lastMovements.pop_back();
    }

    void printCouldMove(){
        cout << "ARESTAS QUE PODEM MOVER: " << endl;
        for(int i=0 ; i<couldMove.size() ; i++)
        {
            cout << "(" << couldMove[i].source.index << " " << couldMove[i].destination.index << "), ";
        }
        cout << endl;
    }

    void print(){
        float perc = percent_between(atrasoInicial, melhorAtraso);
        cout << endl;
        cout << "ATRASO INICIAL: " << atrasoInicial << endl;
        cout << "ATRASO FINAL: " << melhorAtraso << " (" << perc << "%)" << endl;
        bestSolution.print_solution();
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

    vector<int> lastMovements;

    vector< vector<Edge> > criticalPath;
    vector<Edge> couldMove;


};

#endif