#include "ProblemInstance.hpp"

std::string ProblemInstance::instance_name;
std::vector<int> ProblemInstance::vec_priorities;
std::vector<int> ProblemInstance::due_times;
ScheduleMatrix ProblemInstance::vec_schedules;

int ProblemInstance::num_machines;
int ProblemInstance::num_jobs;
int ProblemInstance::num_operations;

bool ProblemInstance::load_instance(string path){

	std::fstream file(path);

	if(!file.is_open()){
		cerr << "FILE WITH PATH: " << path << " WHERE NOT FOUND" << endl;
		return false;
	}

	file >> instance_name;
	file >> num_jobs;
	file >> num_operations;

	num_machines = num_operations;

	vec_schedules.resize(num_jobs);
	vec_priorities.resize(num_jobs);
	due_times.resize(num_jobs);

	Schedule schedule;
	int lixo;
	for(int i=0 ; i<num_jobs ; i++){
		for(int j=0 ; j<num_operations ; j++){

			file >> schedule.machine;
			file >> schedule.time_execution;

			schedule.job = i;
			schedule.task = j; // DEPRECATED
			schedule.operation = j;
			
			vec_schedules[i].push_back(schedule);
		}

		file >> vec_priorities[i];
		file >> lixo;
		file >> due_times[i];
	}

	file.close();

	return true;
}

void ProblemInstance::print(){
	std::cout << instance_name << std::endl;
	std::cout << "Machines: " << num_machines;
	std::cout << " Jobs: " << num_jobs;
	std::cout << " Tasks: " << num_operations << std::endl;

	for(int i=0 ; i<num_jobs ; i++){
		std::cout << "Job " << i << ": ";
		for(int j=0 ; j<num_operations ; j++){
			std::cout << "(" << vec_schedules[i][j].machine << " ";
			std::cout << vec_schedules[i][j].time_execution << ") - ";
		}

		std::cout << vec_priorities[i] << " ";
		std::cout << due_times[i] << std::endl;
	}

	std::cout << std::endl;
}


int ProblemInstance::getNumMachines(){
	return num_machines;
}

int ProblemInstance::getNumJobs(){
	return num_jobs;
}

int ProblemInstance::getNumOperations(){
	return num_operations;
}

int ProblemInstance::getPriorityFromJob(int job){
    return vec_priorities[job];
}

vector<Schedule> ProblemInstance::getOperationsFromJob(int job){
    return vec_schedules[job];
}

vector<int> ProblemInstance::getVecPriorities(){
	return vec_priorities;
}

vector<int> ProblemInstance::getDueTimes(){
	return due_times;
}

int ProblemInstance::getDueTimeFromJob(int job){
	return due_times[job];
}

ScheduleMatrix ProblemInstance::getVecSchedules(){
	return vec_schedules;
}

Schedule ProblemInstance::getSchedule(int job, int op){
	return vec_schedules[job][op];
}