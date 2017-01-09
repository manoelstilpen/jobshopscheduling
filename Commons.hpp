#ifndef COMMONS_HPP
#define COMMONS_HPP

#include <iostream>
#include <vector>

using namespace std;

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

		JobTask(){
			job = task = -1;
		}
	};

	static bool compara_tempo(Schedule p1, Schedule p2) {
		return p1.time_execution < p2.time_execution;
	}

	typedef vector<vector<Schedule>> ScheduleMatrix;
	typedef vector< vector< JobTask >>  Solution;
}

#endif