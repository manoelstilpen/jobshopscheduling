#ifndef DELTA_MOVE_OPT1
#define DELTA_MOVE_OPT1

#include "../Commons.hpp"

using namespace twtjssp;

class DeltaMoveOpt1{
public:
	DeltaMoveOpt1();
	DeltaMoveOpt1(Solution s, int machine, int task, int pos);
	DeltaMoveOpt1(int machine, int task, int pos);

	Solution apply_opt1_move();

	void set_task_number(int);
	void set_machine_number(int);
	void set_pos_number(int);

private:
	Solution solution;

	int machineNumber;
	int taskNumber;
	int posNumber;
};

#endif