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

        Solution() = default;
        Solution(const Solution&);
 
        void aloca_tarefa(Schedule tarefa);
        int time_can_be_alocated(Schedule); /*!< returm the instant the schedule can be allocated */
        int makespan(); /*!< returns the atual solution makespan */

        int size();
        void clear();
        void resize(int i);

        void print_solution();

        void setGraph(Graph);
        
        void setSolution(GanttRepresentation);
        GanttRepresentation getSolution();
        
        GanttRepresentation extract_solution_from_file(string);

        Graph getGraph();

        static void print_solution(GanttRepresentation);

    private:
        Graph graph; /*!< graph representation of solution */
        GanttRepresentation solution;


};

#endif