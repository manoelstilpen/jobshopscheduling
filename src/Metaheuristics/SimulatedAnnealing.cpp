#include "SimulatedAnnealing.hpp"

SimulatedAnnealing::SimulatedAnnealing(){

}

SimulatedAnnealing::SimulatedAnnealing(Solution sol) : Metaheuristic(sol){
    maxIteracoes = ProblemInstance::getNumJobs()*ProblemInstance::getNumMachines();
    alpha = 0.998;
//    temperaturaInicial = 30000;
    temperaturaFinal = 0.01;
}

void SimulatedAnnealing::print_method_informations(){
    cout << "==========================================================================================" << endl;
    cout << " -> SIMULATED ANNEALING <- " << endl;
    cout << "TEMPERATURA INICIAL: " << temperaturaInicial << endl;
    cout << "MAX ITER POR TEMPERATURA: " << maxIteracoes << endl;
}

Solution SimulatedAnnealing::apply(){

    bestSolution = solution;

    melhorAtraso = evaluator.evaluate_by_graph(graph);
    atrasoInicial = melhorAtraso;

    int iterT = 0;  // numero de iteracoes na temperatura T
    int atrasoCorrente = melhorAtraso;
    temperaturaInicial = define_initial_temperature(solution);

    print_method_informations();
    temperatura = temperaturaInicial;
    iterAtual = 0;
    iterTotal = (temperaturaInicial/alpha)*maxIteracoes*7; // nao sei como cheguei nisso
    bool movimentoAceito = false;

    clock_t inicio = clock();
    while(temperatura > temperaturaFinal){
        auto criticalBlocks = graph.getCriticalBlocks();

        while(iterT < maxIteracoes){
            movimentoAceito = false;
            iterT++;
            iterAtual++;

           /* cout << "CRITICAL PATH:" << endl;
            graph.printCriticalPath();

            for(int i=0 ; i<criticalBlocks.size() ; i++){
                for(int j=0 ; j<criticalBlocks[i].size() ; j++){
                    cout << criticalBlocks[i][j].first << " " << criticalBlocks[i][j].second << " ; ";
                }
                cout << endl;
            }
            cout << endl;*/

            ulong randomBlock = rand() % criticalBlocks.size();
            ulong randomEdge = rand() % criticalBlocks[randomBlock].size();

            invert(criticalBlocks[randomBlock][randomEdge]);

            int atraso = evaluator.evaluate_by_graph(graph);

            float delta = atraso - atrasoCorrente;
            if(delta < 0)
            {
                // caso o estado gerado seja de energia menor, o movimento e aceito
                atrasoCorrente = atraso;
                movimentoAceito = true;
                if(atraso < melhorAtraso){
                    melhorAtraso = atraso;
                    bestSolution.setGraph(graph);
                    //cout << melhorAtraso << endl;
                }
            } else {
                double x = (rand() % 100)/100.0;
                float expo = (float(-delta)/float(float(temperatura)));
                double prob = pow(exp(1.0), expo);

                if(x >= prob)
                {
                    // rejeita o movimento, refazendo-o
                    graph.undo_last_movement();
                } else {
                    movimentoAceito = true;
                }
            }

            if(movimentoAceito){
                criticalBlocks = graph.getCriticalBlocks();
            }
        }

        temperatura *= alpha;
        //print_progress();
        //cout << temperatura << endl;
        iterT = 0;
    }

    timeTotal = ((double) (clock() - inicio)/CLOCKS_PER_SEC);

    return bestSolution;
}

float SimulatedAnnealing::define_initial_temperature(Solution s0){

    float t = 100;
    bool continua = true;
    int atrasoCorrente = evaluator.evaluate_by_graph(s0);

    while(continua){
        int aceitos = 0;
        auto criticalBlocks = s0.getGraph().getCriticalBlocks();

        for(int iterT = 0; iterT < maxIteracoes ; iterT++){

            int randomBlock = rand() % criticalBlocks.size();
            int randomEdge = rand() % criticalBlocks[randomBlock].size();

            invert(criticalBlocks[randomBlock][randomEdge]);

            int atraso = evaluator.evaluate_by_graph(graph);
            float delta = atraso - atrasoCorrente;

            if(delta < 0){
                aceitos += 1;
            } else {
                float x = (rand() % 100)/100.0;
                float expo = (float(-delta)/float(float(t)));
                float prob = pow(exp(1.0), expo);
                if(x <= prob)
                    aceitos += 1;
            }

            graph.undo_last_movement();
        }

        if(aceitos >= 0.95 * maxIteracoes){
            continua = false;
        } else {
            t *= 3;
        }
    }   

    return t;
}