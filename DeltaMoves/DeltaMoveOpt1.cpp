#include "DeltaMoveOpt1.hpp"

DeltaMoveOpt1::DeltaMoveOpt1(){

}

DeltaMoveOpt1::DeltaMoveOpt1(Solution s, int machine, int task, int pos){
	this->solution = s;
	this->machineNumber = machine;
	this->taskNumber = task;
	this->posNumber = pos;
}

DeltaMoveOpt1::DeltaMoveOpt1(int machine, int task, int pos){
	this->machineNumber = machine;
	this->taskNumber = task;
	this->posNumber = pos;
}

Solution DeltaMoveOpt1::apply_opt1_move(){
	Schedule job = this->solution[machineNumber][taskNumber];

	if(taskNumber < posNumber){
		for(int i=taskNumber ; i<posNumber ; i++){
			this->solution[machineNumber][i] = this->solution[machineNumber][i+1];
		}
	} else {
		for(int i=taskNumber ; i>posNumber ; i--){
			this->solution[machineNumber][i] = this->solution[machineNumber][i-1];
		}
	}

	this->solution[machineNumber][posNumber] = job;

	return this->solution;
}

void DeltaMoveOpt1::set_task_number(int t){
	this->taskNumber = t;
}

void DeltaMoveOpt1::set_machine_number(int m){
	this->machineNumber = m;
}

void DeltaMoveOpt1::set_pos_number(int p){
	this->posNumber = p;
}