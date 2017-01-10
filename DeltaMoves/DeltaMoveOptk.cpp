#include "DeltaMoveOptk.hpp"

DeltaMoveOptk::DeltaMoveOptk(){

}

DeltaMoveOptk::DeltaMoveOptk(Solution s, int tamBloco, int posNumber){
	this->solution = s;
	this->tamBloco = tamBloco;
	this->posNumber = posNumber;
}

DeltaMoveOptk::DeltaMoveOptk(int tamBloco, int posNumber){
	this->tamBloco = tamBloco;
	this->posNumber = posNumber;
}

Solution DeltaMoveOptk::apply_optk_move(){

}

void DeltaMoveOptk::set_solution(Solution s){
	this->solution = s;
}

void DeltaMoveOptk::set_tam_bloco(int t){
	this->tamBloco = t;
}

void DeltaMoveOptk::set_pos_number(int p){
	this->posNumber = p;
}