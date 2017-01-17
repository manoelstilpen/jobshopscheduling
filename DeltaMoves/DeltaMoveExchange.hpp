#ifndef DELTA_MOVE_EXCHANGE
#define DELTA_MOVE_EXCHANGE

#include "../Commons.hpp"
#include "../ProblemInstance.hpp"

using namespace twtjssp;

class DeltaMoveExchange{

public:
	DeltaMoveExchange();
	DeltaMoveExchange(ProblemInstance p, Solution sol, int machine, int pos1, int pos2);
	DeltaMoveExchange(int machine, int pos1, int pos2);
	DeltaMoveExchange(ProblemInstance p);

	Solution apply_exchange_move();
	void fix_solution();

	void set_instance(ProblemInstance);
	void set_solution(Solution);
	void set_positions(int mach, int pos1, int pos2);
	void set_machine_number(int);
	void set_pos1(int);
	void set_pos2(int);

private:
	ProblemInstance instance;
	Solution solution;
	ScheduleMatrix jobs;

	int machineNumber;
	int pos1Index;
	int pos2Index;

};

#endif