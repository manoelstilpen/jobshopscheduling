#ifndef CONSTRUCTIVE_HPP
#define CONSTRUCTIVE_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "../Evaluator.hpp"

class Constructive {

    public:

        virtual Solution apply() = 0;

        Constructive(){

        }

        Constructive(ProblemInstance p) : solution(p), evaluator(p) {
            this->repeat = 1;
            this->instance = p;
            this->nMachines = p.get_num_machines();
            this->nJobs = p.get_num_jobs();
            this->nOperations = p.get_num_tasks();
        }

        void print(){
            for(int i=0 ; i<solution.size() ; i++){
                cout << "MACHINE " << i << ": ";
                for(int j=0 ; j<solution[i].size() ; j++){
                    cout << "(" << solution[i][j].job << "," << solution[i][j].task << "," << solution[i][j].time_execution << ") - ";
                }
                cout << endl;
            }

            evaluator.print();
        }

        void set_repeat(int t){ this->repeat = t;}
        int get_media_atraso(){ return this->media_atraso;}
        
    protected:
        Solution solution;
        Evaluator evaluator;
        ProblemInstance instance;

	    int repeat;
	    int media_atraso;

        int nMachines;
        int nJobs;
        int nOperations;
};

#endif