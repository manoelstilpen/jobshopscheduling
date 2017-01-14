#include "Commons.hpp"

namespace twtjssp{

    Solution aloca_tarefa(Solution* solution, ScheduleMatrix* jobs, Schedule tarefa){
        /* Aloca a tarefa e retorna a nova solucao */

        int machine = tarefa.machine;
        int sizeMachine = (*solution)[machine].size(); // quantidade de tasks alocadas na maquina

        if(tarefa.task == 0){
            // Se for a primeira tarefa do job, existe tarefas anteriores para serem analisadas
            if((*solution)[machine].size() == 0){
                // Como nao tem outra tarefa alocada nessa maquina, apenas insere a tarefa na maquina
                (*solution)[machine].push_back(tarefa); // aloca a tarefa na maquina
            } else {
                // Armazena o tempo acumulado da maquina e adiciona ao tempo da nova tarefa
                int tempo = (*solution)[machine][sizeMachine-1].time_execution; // armazena o tempo acumulado
                tarefa.time_execution += tempo; // adiciona o tempo acumulado
                (*solution)[machine].push_back(tarefa); // aloca a tarefa na maquina
            }

        } else {
            /* Nesse caso, deve-se procurar pela ultima tarefa executada do job e armazenar
             * seu instante de conclusao. Depois, analisar o tempo da maquina atual e comparar 
             * com o instante que terminou a ultima tarefa, para nao quebrar a regra que afirma
             * que uma tarefa de um job nao pode começar antes da anterior terminar.
             */

            // Maquina que executou a ultima tarefa do job
            int lastMachine = (*jobs)[tarefa.job][tarefa.task-1].machine;

            int timeLastTask = 0;
            // Procura pelo instante que a ultima task DO JOB foi finalizada
            for(int i=0 ; i<(*solution)[lastMachine].size() ; i++){
                if((*solution)[lastMachine][i].job == tarefa.job){
                    timeLastTask = (*solution)[lastMachine][i].time_execution;
                    break;
                }
            }

            // Tempo acumulado da maquina que a tarefa deve ser inserida
            int timeMachine = 0;
            if(sizeMachine != 0){
                timeMachine = (*solution)[machine][sizeMachine-1].time_execution;
            }
            
            if(timeMachine > timeLastTask){
                /* Se o tempo acumulado da maquina atual for MAIOR que o instante em que a ultima tarefa
                 * foi finalizada, pode inserir a tarefa atual imediatamente depois.
                 */
                tarefa.time_execution += (*solution)[machine][sizeMachine-1].time_execution;
                (*solution)[machine].push_back(tarefa);
            } else {
                /* Se o tempo acumulado da maquina atual for MENOR do que o instante em que a ultima tarefa
                 * foi finalizada, cria-se uma janela na producao na maquina. 
                 */
                tarefa.time_execution += timeLastTask;
                (*solution)[machine].push_back(tarefa);
            }
        }

        return *solution;
    }
}