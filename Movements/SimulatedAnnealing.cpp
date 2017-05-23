#include "SimulatedAnnealing.hpp"

SimulatedAnnealing::SimulatedAnnealing(){

}

SimulatedAnnealing::SimulatedAnnealing(Solution sol) : Movement(sol){
    maxIteracoes = instance.get_num_jobs()*instance.get_num_machines()*0.5;
    alpha = 0.99;
    temperaturaInicial = 70;
    temperaturaFinal = 0.5;
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
    iterTotal = (temperaturaInicial/alpha)*maxIteracoes*7; // nao sei como cheguei
    bool movimentoAceito = false;

    clock_t inicio = clock();
    while(temperatura > temperaturaFinal){
        updateCouldMove();

        while(iterT < maxIteracoes){
            movimentoAceito = false;
            iterT++;
            iterAtual++;

            int randomEdge = rand() % couldMove.size();

            graph.invert(couldMove[randomEdge].index);

    //        Solution::print_solution(graph.generate_gantt());
            int atraso = evaluator.evaluate_by_graph(graph);

//            cout << "ATRASO: " << atraso << endl;
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
                    bestSolution.setSolution(graph.generate_gantt());
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
                    graph.invert(couldMove[randomEdge].index);
                } else {
  //                  cout << "ACEITOU PIORA " << x << " " << prob << endl;
                    movimentoAceito = true;
                }
            }

            if(movimentoAceito){
                updateCouldMove();
            }
        }

        temperatura *= alpha;
        print_progress();
  //      cout << temperatura << endl;
        iterT = 0;
    }

    print();
    cout << "ITERACOES: " << iterAtual << endl;
    float seg = ((double) (clock() - inicio)/CLOCKS_PER_SEC);
    cout << "TEMPO:     " << seg << "s => " << seg/60 << "min" << endl;

    return solution;
}