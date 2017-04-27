#include "SimulatedAnnealing.hpp"

SimulatedAnnealing::SimulatedAnnealing(){

}

SimulatedAnnealing::SimulatedAnnealing(Solution sol) : Movement(sol){
    maxIteracoes = instance.get_num_jobs()*instance.get_num_machines()*1;
//    maxIteracoes = 20;
    alpha = 0.95;
    temperaturaInicial = 75;
    temperaturaFinal = 0.01;
}

Solution SimulatedAnnealing::apply(){

    bestSolution = solution;

    graph.bellmanFord();

    melhorAtraso = evaluator.evaluate_by_graph(graph);
    atrasoInicial = melhorAtraso;

    cout << "==========================================================================================" << endl;
    cout << " -> SIMULATED ANNEALING <- " << endl;
    cout << "TEMPERATURA INICIAL: " << temperaturaInicial << endl;
    cout << "MAX ITER POR ITERACAO: " << maxIteracoes << endl;

    int iterT = 0;  // numero de iteracoes na temperatura T
    int atrasoCorrente = melhorAtraso;
    temperatura = temperaturaInicial;
    int cont=0;

    clock_t inicio = clock();
    while(temperatura > temperaturaFinal){
        while(iterT < maxIteracoes){

            iterT++;
            cont++;

            updateCouldMove();

            int randomEdge = rand() % couldMove.size();

//            cout << "TROCANDO " << couldMove[randomEdge].source.index << "-" << couldMove[randomEdge].destination.index << endl;

            graph.invert(couldMove[randomEdge].index);

    //        Solution::print_solution(graph.generate_gantt());
            int atraso = evaluator.evaluate_by_graph(graph);

    //        cout << "ATRASO: " << atraso << endl;
            float delta = atraso - atrasoCorrente;
            if(delta < 0)
            {
                // caso o estado gerado seja de energia menor, o movimento e aceito
                atrasoCorrente = atraso;

                if(atraso < melhorAtraso)
                {
                    melhorAtraso = atraso;
                    bestSolution.setSolution(graph.generate_gantt());
                    bestSolution.setGraph(graph);
                }
            }
            else
            {
                float x = (rand() % 100)/100.0;
                float expo = (-delta/(boltzmann*temperatura));
                float prob = pow(euler, expo);

                if(x >= prob)
                {
                    // rejeita o movimento, refazendo-o
                    graph.invert(couldMove[randomEdge].index);
                } else {
//                    cout << "aceitou piora" << endl;
                }
            }
        }

        temperatura *= alpha;
//        cout << temperatura << endl;
        iterT = 0;
    }

    print();
    cout << "ITERACOES: " << cont << endl;
    float seg = ((double) (clock() - inicio)/CLOCKS_PER_SEC);
    cout << "TEMPO:     " << seg << "s => " << seg/60 << "min" << endl;

    return solution;
}