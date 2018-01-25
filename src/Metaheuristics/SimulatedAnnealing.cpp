#include "SimulatedAnnealing.hpp"

SimulatedAnnealing::SimulatedAnnealing(){

}

SimulatedAnnealing::SimulatedAnnealing(Solution sol) : Metaheuristic(sol){
    maxIteracoes = 2*instance.get_num_jobs()*instance.get_num_machines();
    alpha = 0.998;
    temperaturaInicial = 30000;
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

    graph.bellmanFord();

    melhorAtraso = evaluator.evaluate_by_graph(graph);
    atrasoInicial = melhorAtraso;

    print_method_informations();

    int iterT = 0;  // numero de iteracoes na temperatura T
    int atrasoCorrente = melhorAtraso;
    temperatura = temperaturaInicial;
    iterAtual = 0;
    iterTotal = (temperaturaInicial/alpha)*maxIteracoes*7; // nao sei como cheguei nisso
    bool movimentoAceito = false;

    clock_t inicio = clock();
    while(temperatura > temperaturaFinal){
        updateCouldMove();

        while(iterT < maxIteracoes){
            movimentoAceito = false;
            iterT++;
            iterAtual++;

            int randomBlock = rand() % criticalBlocks.size();
            int randomEdge = rand() % criticalBlocks[randomBlock].size();

            invert(criticalBlocks[randomBlock][randomEdge]);

            int atraso = evaluator.evaluate_by_graph(graph);

            float delta = atraso - atrasoCorrente;
            if(delta < 0)
            {
                // caso o estado gerado seja de energia menor, o movimento e aceito
                atrasoCorrente = atraso;
                movimentoAceito = true;
                if(atraso < melhorAtraso)
                {
  //                  cout << "TROCADO " << couldMove[randomEdge].source.index << "-" << couldMove[randomEdge].destination.index << endl;
//                    cout << "OTIMO LOCAL " << atraso << endl;
                    melhorAtraso = atraso;

                    bestSolution.setGraph(graph);
                }

            }
            else
            {
                float x = (rand() % 100)/100.0;
                float expo = (float(-delta)/float(float(temperatura)));
                float prob = pow(exp(1.0), expo);
//                cout << exp(1.0) << "^" << expo << "=" << prob << endl;
//                cout << x << " " << prob << endl;
                if(x >= prob)
                {
                    // rejeita o movimento, refazendo-o
                    undo_last_movement();
                } else {
//                    cout << "ACEITOU PIORA " << x << " " << prob << " " << iterT << endl;
                    movimentoAceito = true;
                }
            }

            if(movimentoAceito){
                updateCouldMove();
            }
        }

        temperatura *= alpha;
        print_progress();
        cout << temperatura << endl;
        iterT = 0;
    }

    timeTotal = ((double) (clock() - inicio)/CLOCKS_PER_SEC);

    return bestSolution;
}