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

        int size();
        void clear();
        void resize(int i);

        inline void print_solution(Solution sol);

    private:
        ProblemInstance instance;
        vector<vector<Schedule>> solution;


};

#endif