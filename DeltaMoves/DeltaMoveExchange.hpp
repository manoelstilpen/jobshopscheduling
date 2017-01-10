#ifndef DELTA_MOVE_EXCHANGE
#define DELTA_MOVE_EXCHANGE

#include "../Commons.hpp"

using namespace twtjssp;

class DeltaMoveExchange{

public:
	DeltaMoveExchange();
	DeltaMoveExchange(Solution sol, int machine, int pos1, int pos2);
	DeltaMoveExchange(int machine, int pos1, int pos2);

	Solution apply_exchange_move();

	void set_solution(Solution);
	void set_machine_number(int);
	void set_pos1(int);
	void set_pos2(int);

private:
	Solution solution;

	int machineNumber;
	int pos1Number;
	int pos2Number;

};

#endif