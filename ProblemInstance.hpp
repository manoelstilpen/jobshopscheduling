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

	void load_instance();
	void print();

	void set_name_file(std::string);

	int get_num_machines();
	int get_num_jobs();
	int get_num_tasks();
	std::string get_name_file();
	std::string get_instance_name();
	std::vector<int> get_vec_priorities();
	std::vector<int> get_vec_conclusion_times();
	ScheduleMatrix get_vec_schedules();
	Schedule get_vec_schedules(int job, int task);


private:
	std::string instance_file_name;
	std::string instance_name;
	std::vector<int> vec_priorities;
	std::vector<int> vec_conclusion_times;
	ScheduleMatrix vec_schedules;

	int num_machines;
	int num_jobs;
	int num_tasks;

};

#endif