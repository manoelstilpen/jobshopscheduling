#ifndef COMMONS_HPP
#define COMMONS_HPP

#include <iostream>
#include <vector>

namespace twtjssp{

	struct Schedule{
		int machine;
		int time_execution;

		Schedule(){
			machine = time_execution = -1;
		}

		Schedule(int m, int t){
			machine = m;
			time_execution = t;
		}
	};

	typedef std::vector<std::vector<Schedule>> ScheduleMatrix;

}

#endif