#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Commons.hpp"
#include "ProblemInstance.hpp"

using namespace twtjssp;

class Solution {

    public:

        void operator+=(const Schedule schedule){
            aloca_tarefa(schedule);
        }

        vector<Schedule> operator[](const int& i){
            return this->solution[i];
        }

        Solution();
        Solution(ProblemInstance);
 
        void aloca_tarefa(Schedule tarefa);
        int time_can_be_alocated(Schedule); /*!< returm the instant the schedule can be allocated */

        int size();
        void clear();
        void resize(int i);

        inline void print_solution();
        inline void print_graphic();

    private:
        ProblemInstance instance;
        vector<vector<Schedule>> solution;


};

#endif