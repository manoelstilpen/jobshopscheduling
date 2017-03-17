#ifndef CRUD_HPP
#define CRUD_HPP

#include "Commons.hpp"

#include <fstream>
#include <iostream>

using namespace twtjssp;

class ProblemInstance{

public:
	ProblemInstance();
	ProblemInstance(std::string);

	bool load_instance();
	void print();

	void set_name_file(string);

	int get_num_machines();
	int get_num_jobs();
	int get_num_tasks();
	std::string get_name_file();
	string get_instance_name();
	std::vector<int> get_vec_priorities();
	std::vector<int> get_due_times();
	int get_due_times(int);
	ScheduleMatrix get_vec_schedules();
	Schedule get_vec_schedules(int job, int task);


private:
	string instance_file_name;
	std::string instance_name;
	std::vector<int> vec_priorities;
	std::vector<int> due_times;
	ScheduleMatrix vec_schedules;

	int num_machines;
	int num_jobs;
	int num_tasks;

};

#endif