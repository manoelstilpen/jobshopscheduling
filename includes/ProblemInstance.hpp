#ifndef CRUD_HPP
#define CRUD_HPP

#include "Commons.hpp"

#include <fstream>
#include <iostream>

using namespace twtjssp;

class ProblemInstance {

public:

//    ProblemInstance();
//
//	vector<Schedule> operator[](const int& i){
//		return vec_schedules[i];
//	}

	static bool load_instance(string path);

	static void print();
    static int getNumMachines();
    static int getNumJobs();
	static int getNumOperations();

    static int getPriorityFromJob(int job);

    static vector<Schedule> getOperationsFromJob(int job);
    static vector<int> getVecPriorities();
    static vector<int> getDueTimes();

	static int getDueTimeFromJob(int);
    static ScheduleMatrix getVecSchedules();

	static Schedule getSchedule(int job, int task);

private:

    static std::string instance_name;
    static std::vector<int> vec_priorities;
    static std::vector<int> due_times;
    static ScheduleMatrix vec_schedules;

	static int num_machines;
	static int num_jobs;
//	static int num_tasks;
    static int num_operations;

};

#endif