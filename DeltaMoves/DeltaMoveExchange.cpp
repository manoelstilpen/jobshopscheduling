#include "DeltaMoveExchange.hpp"

DeltaMoveExchange::DeltaMoveExchange(){

}

DeltaMoveExchange::DeltaMoveExchange(Solution solution, int machine, int pos1, int pos2){
	this->solution = solution;
	this->machineNumber = machine;
	this->pos1Number = pos1;
	this->pos2Number = pos2;
}

DeltaMoveExchange::DeltaMoveExchange(int machine, int pos1, int pos2){
	this->machineNumber = machine;
	this->pos1Number = pos1;
	this->pos2Number = pos2;
}

Solution DeltaMoveExchange::apply_exchange_move(){
	JobTask aux = this->solution[machineNumber][pos1Number];
	this->solution[machineNumber][pos1Number] = this->solution[machineNumber][pos2Number];
	this->solution[machineNumber][pos2Number] = aux;

	//printSolution(10, 10, this->solution);

	return this->solution;
}

void DeltaMoveExchange::set_solution(Solution sol){
	this->solution = sol;
}

void DeltaMoveExchange::set_machine_number(int machine){
	this->machineNumber = machine;
}

void DeltaMoveExchange::set_pos1(int num){
	this->pos1Number = num;
}

void DeltaMoveExchange::set_pos2(int num){
	this->pos2Number = num;
}