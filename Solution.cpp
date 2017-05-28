#include "Solution.hpp"

Solution::Solution(){

}

Solution::Solution(ProblemInstance p){
    this->instance = p;
    graph.set_instance(p);
}

void Solution::aloca_tarefa(Schedule tarefa){
    /* Aloca a tarefa na solucao */

    int machine = tarefa.machine;
    int sizeMachine = this->solution[machine].size(); // quantidade de tasks alocadas na maquina

    // caso seja a primeira operacao do job
    if(tarefa.task == 0){
    
        if(this->solution[machine].size() == 0){
            // Como nao tem outra tarefa alocada nessa maquina, apenas insere a tarefa na maquina
            this->solution[machine].push_back(tarefa);
        } else {
            // Armazena o tempo acumulado da maquina e adiciona ao tempo da nova tarefa
            int tempo = this->solution[machine][sizeMachine-1].time_execution;
            tarefa.time_execution += tempo; // adiciona o tempo acumulado
            this->solution[machine].push_back(tarefa); // aloca a tarefa na maquina
        }

    } else {
        /* Nesse caso, deve-se procurar pela ultima tarefa executada do job e armazenar
         * seu instante de conclusao. Depois, analisar o tempo da maquina atual e comparar 
         * com o instante que terminou a ultima tarefa da maquina, para nao quebrar a regra que afirma
         * que uma tarefa de um job nao pode começar antes da anterior terminar.
         */

        // Maquina que executou a ultima tarefa do job
        int lastMachine = instance[tarefa.job][tarefa.task-1].machine;

        int timeLastTask = 0;
        // Procura pelo instante que a ultima operacao DO JOB foi finalizada
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

int Solution::time_can_be_alocated(Schedule op){
    // retorna o tempo que a operacao pode ser inicializada
    
    // tempo atual da maquina da operacao op
    int timeMachine = [&]() {
        if(solution[op.machine].size() == 0) return 0;
        else return solution[op.machine].back().time_execution;
    }();
    
    // tempo de termino da ultima operacao 
    int lastOperation = [&]() {
        if(op.task == 0) return 0;

        int lastMachine = instance[op.job][op.task-1].machine;
        for(Schedule i : solution[lastMachine]){
            if(i.job == op.job){
                return i.time_execution;
            }
        }

        return 0;
    }();

    return max(timeMachine, lastOperation);
}

// 4358 -> ATRASO DA SOLUCAO VIA OPTFRAME
GanttRepresentation Solution::extract_solution_from_file(string filename){

    std::fstream file(filename);

    if(!file.is_open()){
	    std::cout << "ERROR: FILE NOT FOUND" << std::endl;
	}

    string nome_instancia;
    file >> nome_instancia; 

    if(instance.get_instance_name().compare(nome_instancia) != 0){
        cout << "SOLUCAO NAO CORRESPONDE COM A INSTANCIA CARREGADA" << endl;
    }

    solution.resize(instance.get_num_jobs());

    int job, op;
    for(int i=0 ; i<instance.get_num_jobs() ; i++){
        for(int j=0 ; j<instance.get_num_operations() ; j++){
            file >> job;
            file >> op;

            solution[i].push_back(Schedule(job, op, i));
            
        }
    } 

    int t1, t2;
    for(int i=0 ; i<instance.get_num_jobs() ; i++){
        for(int j=0 ; j<instance.get_num_operations() ; j++){

            file >> t1;
            file >> t2;

            solution[i][j].time_execution = t2;
        }
    }

    file.close();

    graph.construct_conjuctive_graph();
    graph.construct_disjuntive_graph(solution);

    return solution;
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

void Solution::print_solution(){
    for(int i=0 ; i<solution.size() ; i++){
        cout << "MACHINE " << i << ": ";
        for(int j=0 ; j<solution[i].size() ; j++){
            cout << "(" << solution[i][j].job << "," << solution[i][j].task << "," << solution[i][j].time_execution << ") - ";
        }
        cout << endl;
    }
    cout << "==========================================================================================" << endl;
}

inline void Solution::print_graphic(){

}

void Solution::setGraph(Graph g){
    this->graph = g;
}

void Solution::setSolution(GanttRepresentation s){
    this->solution = s;
}

GanttRepresentation Solution::getSolution(){
    return this->solution;
}

Graph Solution::getGraph(){
    return this->graph;
}

ProblemInstance Solution::getInstance(){
    return this->instance;
}

void Solution::print_solution(GanttRepresentation solution){
    for(int i=0 ; i<solution.size() ; i++){
        cout << "MACHINE " << i << ": ";
        for(int j=0 ; j<solution[i].size() ; j++){
            cout << "(" << solution[i][j].job << "," << solution[i][j].task << "," << solution[i][j].time_execution << ") - ";
        }
        cout << endl;
    }
    cout << "==========================================================================================" << endl;
}