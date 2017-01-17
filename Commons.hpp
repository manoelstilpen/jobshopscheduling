#ifndef COMMONS_HPP
#define COMMONS_HPP

#define INF 99999999;

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

//Total Weighted Tardiness Job-Shop Scheduling
namespace twtjssp{

	struct Schedule{
		int job;
		int task;
		int machine;
		int time_execution;

		Schedule(){
			machine = time_execution = -1;
			job = task = -1;
		}

		Schedule(int m, int t){
			machine = m;
			time_execution = t;
		}

		Schedule(int j, int t, int tm){
			job = j;
			task = t;
			time_execution = tm;
		}
	};

	struct JobTask{
		int job;	// as first
		int task;	// as second

		JobTask(int j, int t){
			this->job = j;
			this->task = t;
		}

		JobTask(){
			job = task = -1;
		}

		void print(){
			cout << "JobTask: Job: " << job;
			cout << " Task: " << task << endl;
		}
	};

	typedef vector<vector<Schedule>> ScheduleMatrix;
	typedef vector< vector<Schedule>>  Solution;

	static bool compara_tempo(Schedule p1, Schedule p2) {
		return p1.time_execution < p2.time_execution;
	}

	static bool compara_task(Schedule p1, Schedule p2){
		return p1.task < p2.task;
	}

	inline void print_solution(Solution sol){
		for(int i=0 ; i<sol.size() ; i++){
			cout << "MACHINE " << i << ": ";
			for(int j=0 ; j<sol[i].size() ; j++){
				cout << "(" << sol[i][j].job << "," << sol[i][j].task << "," << sol[i][j].time_execution << ") - ";
			}
			cout << endl;
		}
		cout << "==========================================================================================" << endl;
	}

	inline void print_schedule(Schedule s){
		cout << "(" << s.job << "," << s.task << "," << s.machine << "," << s.time_execution << ") - ";
	}

	Solution aloca_tarefa(Solution* solution, ScheduleMatrix* jobs, Schedule tarefa);

}

#endif