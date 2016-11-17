#include "ProblemInstance.hpp"

ProblemInstance::ProblemInstance(){
	instance_name = "NULL";
	num_tasks = -1;
	num_jobs = -1;
	num_machines = -1;
}

ProblemInstance::ProblemInstance(std::string name){
	set_name_file(name);
}

void ProblemInstance::load_instance(){

	std::fstream file(this->instance_file_name);

	if(!file.is_open()){
		std::cout << "FILE NOT FOUND" << std::endl;
		return;
	}

	file >> this->instance_name;
	file >> this->num_machines;
	file >> this->num_jobs;
	this->num_tasks = this->num_jobs;

	this->vec_schedules.resize(this->num_jobs);
	this->vec_priorities.resize(this->num_jobs);
	this->vec_conclusion_times.resize(this->num_jobs);

	Schedule schedule;
	int lixo;
	for(int i=0 ; i<this->num_machines ; i++){
		for(int j=0 ; j<this->num_tasks ; j++){
			file >> schedule.machine;
			file >> schedule.time_execution;
			this->vec_schedules[i].push_back(schedule);
		}

		file >> this->vec_priorities[i];
		file >> lixo;
		file >> this->vec_conclusion_times[i];
	}

	file.close();
}

void ProblemInstance::print(){
	std::cout << this->instance_name << std::endl;
	std::cout << "Machines: " << this->num_machines;
	std::cout << " Jobs: " << this->num_jobs;
	std::cout << " Tasks: " << this->num_tasks << std::endl;

	for(int i=0 ; i<this->num_jobs ; i++){
		for(int j=0 ; j<this->num_tasks ; j++){
			std::cout << "(" << this->vec_schedules[i][j].machine << " ";
			std::cout << this->vec_schedules[i][j].time_execution << ") - ";
		}

		std::cout << this->vec_priorities[i] << " ";
		std::cout << this->vec_conclusion_times[i] << std::endl;
	}
}

void ProblemInstance::set_name_file(std::string name){
	if(name.find("Instances/") == 0){
		this->instance_file_name = name;	
	} else {
		std::string aux("Instances/");
		aux += name;
		this->instance_file_name = aux;
	}
}

int ProblemInstance::get_num_machines(){
	return this->num_machines;
}

int ProblemInstance::get_num_jobs(){
	return this->num_jobs;
}

int ProblemInstance::get_num_tasks(){
	return this->num_tasks;
}

std::string ProblemInstance::get_name_file(){
	return this->instance_file_name;
}

std::string ProblemInstance::get_instance_name(){
	return this->instance_name;
}

std::vector<int> ProblemInstance::get_vec_priorities(){
	return this->vec_priorities;
}

std::vector<int> ProblemInstance::get_vec_conclusion_times(){
	return this->vec_conclusion_times;
}

ScheduleMatrix ProblemInstance::get_vec_schedules(){
	return this->vec_schedules;
}