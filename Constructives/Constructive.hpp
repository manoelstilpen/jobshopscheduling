#ifndef CONSTRUCTIVE_HPP
#define CONSTRUCTIVE_HPP

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"
#include "../Evaluator.hpp"

/**
 * Pure Virtual class to create a constructive method
 */

class Constructive {

    public:

        virtual Solution apply() = 0;
        virtual void print_method_informations() = 0;

        Constructive(){

        }

        Constructive(ProblemInstance p) : solution(p), evaluator(p) {
            this->repeat = 1;
            this->instance = p;
            this->nMachines = p.get_num_machines();
            this->nJobs = p.get_num_jobs();
            this->nOperations = p.get_num_tasks();
        }

        /**
         * Method which prints the solution generated so far
         */
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

        virtual void print_graphic(){
            cout << this->media_atraso << endl;
        }

        void set_repeat(int t){ this->repeat = t;}
        int get_atraso(){ return this->media_atraso;}
        
    protected:
        Solution solution;
        Evaluator evaluator;
        ProblemInstance instance;

	    int repeat;         /*!< defines how many times the methos will run */
	    int media_atraso;   /*!< stores the medium value of tardiness between all solutions generated */

        int nMachines;
        int nJobs;
        int nOperations;
};

#endif