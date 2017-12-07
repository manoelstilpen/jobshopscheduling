#ifndef COMMONS_HPP
#define COMMONS_HPP

#define INF 99999999

#define GHOSTNODES 2
#define INITNODE 1

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <ctime>
#include <functional>

using namespace std;

//Total Weighted Tardiness Job-Shop Scheduling Problem
namespace twtjssp{
	
	// CONJUNCAO => e
	// DISJUNCAO => ou

	struct Schedule{
		int job;
		int task, operation;
		int machine;
		int time_execution;

		Schedule(){
			machine = time_execution = -1;
			job = task = operation = -1;
		}

		Schedule(int m, int t){
			machine = m;
			time_execution = t;
		}

		Schedule(int j, int t, int m){
			job = j;
			task = operation = t;
			machine = m;
		}

/*		Schedule(int j, int t, int tm){
			job = j;
			task = t;
			time_execution = tm;
		}*/

		Schedule(int j, int t, int m, int tm){
			job = j;
			operation = task = t;
			machine = m;
			time_execution = tm;
		}
	};
	
	struct Node{
		int job;
		int operation;
		int weight;
		int index;

		Node(){
			job = operation = -1;
		}

		Node(int job, int op, int id, int weight){
			this->job = job;
			this->index = id;
			this->operation = op;
			this->weight = weight;
		}

		string toString(){
			stringstream ss;
			ss << "(" << job << "-" << operation << ": " << index << ")";
			return ss.str();
		}

		bool operator==(const Node& n1){
    		return (job == n1.job && operation == n1.operation);
		}

		bool operator!=(const Node& n1){
    		return !(job == n1.job && operation == n1.operation);
		}
	};

	typedef vector< vector<Schedule> > ScheduleMatrix;
	typedef vector< vector<Schedule> > GanttRepresentation;

	static bool compara_tempo(Schedule p1, Schedule p2) {
		return p1.time_execution < p2.time_execution;
	}

	static bool compara_task(Schedule p1, Schedule p2){
		return p1.task < p2.task;
	}

	inline void print_schedule(Schedule s){
		cout << "(" << s.job << "," << s.task << "," << s.machine << "," << s.time_execution << ") - ";
	}

	inline float percent_between(float a, float b){
		return (((float)a/(float)b)-1)*100.f;
	}

	inline bool verify_critical(Schedule src, Schedule dest){
		if(src.job != dest.job && src.job != -1 && dest.job != -1) return true;

		return false;
	}

	inline vector<int> stack_to_vector(stack<int> stack){
		int* end   = &stack.top() + 1;
    	int* begin = end - stack.size();

    	std::vector<int> stack_contents(begin, end);
    	std::reverse(stack_contents.begin(), stack_contents.end());

		return stack_contents;
	}
}

#endif