#include "Solution.hpp"

Solution::Solution(){

}

Solution::Solution(ProblemInstance p){
    this->instance = p;
}

void Solution::aloca_tarefa(Schedule tarefa){
    /* Aloca a tarefa na solucao */

    int machine = tarefa.machine;
    int sizeMachine = this->solution[machine].size(); // quantidade de tasks alocadas na maquina

    if(tarefa.task == 0){
        // Se for a primeira tarefa do job, existe tarefas anteriores para serem analisadas
        if(this->solution[machine].size() == 0){
            // Como nao tem outra tarefa alocada nessa maquina, apenas insere a tarefa na maquina
            this->solution[machine].push_back(tarefa); // aloca a tarefa na maquina
        } else {
            // Armazena o tempo acumulado da maquina e adiciona ao tempo da nova tarefa
            int tempo = this->solution[machine][sizeMachine-1].time_execution; // armazena o tempo acumulado
            tarefa.time_execution += tempo; // adiciona o tempo acumulado
            this->solution[machine].push_back(tarefa); // aloca a tarefa na maquina
        }

    } else {
        /* Nesse caso, deve-se procurar pela ultima tarefa executada do job e armazenar
            * seu instante de conclusao. Depois, analisar o tempo da maquina atual e comparar 
            * com o instante que terminou a ultima tarefa, para nao quebrar a regra que afirma
            * que uma tarefa de um job nao pode começar antes da anterior terminar.
            */

        // Maquina que executou a ultima tarefa do job
        int lastMachine = instance[tarefa.job][tarefa.task-1].machine;

        int timeLastTask = 0;
        // Procura pelo instante que a ultima task DO JOB foi finalizada
        for(int i=0 ; i<this->solution[lastMachine].size() ; i++){
            if(this->solution[lastMachine][i].job == tarefa.job){
                timeLastTask = this->solution[lastMachine][i].time_execution;
                break;
            }
        }

        // Tempo acumulado da maquina que a tarefa deve ser inserida
        int timeMachine = 0;
        if(sizeMachine != 0){
            timeMachine = this->solution[machine][sizeMachine-1].time_execution;
        }
        
        if(timeMachine > timeLastTask){
            /* Se o tempo acumulado da maquina atual for MAIOR que o instante em que a ultima tarefa
             * foi finalizada, pode inserir a tarefa atual imediatamente depois.
             */
            tarefa.time_execution += this->solution[machine][sizeMachine-1].time_execution;
            this->solution[machine].push_back(tarefa);
        } else {
            /* Se o tempo acumulado da maquina atual for MENOR do que o instante em que a ultima tarefa
                * foi finalizada, cria-se uma janela na producao na maquina. 
                */
            tarefa.time_execution += timeLastTask;
            this->solution[machine].push_back(tarefa);
        }
    }
}

int Solution::size(){
    return this->solution.size();
}

void Solution::clear(){
    for(int i=0 ; i<this->solution.size() ; i++){
        this->solution[i].clear();
    }
}

void Solution::resize(int i){
    this->solution.resize(i);
}

inline void print_solution(Solution sol){
    for(int i=0 ; i<sol.size() ; i++){
        cout << "MACHINE " << i << ": ";
        for(int j=0 ; j<sol[i].size() ; j++){
            cout << "(" << sol[i][j].job << "," << sol[i][j].task << "," << sol[i][j].time_execution << ") - ";
        }
        cout << endl;
    }
    cout << "==========================================================================================" << endl;
}