#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Commons.hpp"
#include "ProblemInstance.hpp"
#include "Graph.hpp"

#include <fstream>

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

        void print_solution();
        inline void print_graphic();

        void setGraph(Graph);
        
        void setSolution(GanttRepresentation);
        GanttRepresentation getSolution();
        
        GanttRepresentation extract_solution_from_file(string);

        Graph getGraph();

        ProblemInstance getInstance();


        static void print_solution(GanttRepresentation);

    private:
        ProblemInstance instance;
        Graph graph; /*!< graph representation of solution */
        GanttRepresentation solution;


};

#endif