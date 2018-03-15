#ifndef CONSTRUCTIVE_HPP
#define CONSTRUCTIVE_HPP

#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "Evaluator.hpp"

/**
 * Pure Virtual class to create a constructive method
 */

class Constructive {

    public:

        Constructive();
        Constructive(double _alpha);
        
        virtual Solution apply();
        virtual void print_method_informations() = 0;


        /**
         * Method which prints the solution generated so far
         */
        void print();

        virtual void print_graphic();

        void set_repeat(int t);
        int get_atraso();
        
    protected:
        Solution solution;
        Evaluator evaluator;

	    int repeat;         /*!< defines how many times the methods will execute */
	    int media_atraso;   /*!< stores the medium value of tardiness between all solutions generated */

        int nMachines;
        int nJobs;
        int nOperations;

        double alpha;   			/*!< defines how greedy will be your grasp  */

        vector<int> restricts; 		/*!< restricts operations */

        virtual float define_priority(Schedule op) = 0; /*!< method used to evaluate a schedule */
        virtual int choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts) = 0;

        virtual float valor_grasp(const float& min, const float& max);  /*!< returns the value which defines the operation's restrict list */
	    void remove_choosed_schedule(ScheduleMatrix& jobs_temp, int index);

        struct Custo{
            int indice;
            float custo;

            Custo(){
                indice = custo = 0;
            }

            Custo(int i, float c){
                this->indice = i;
                this->custo = c;
            }
	    };
};

#endif