#ifndef DELTA_MOVE_OPTK
#define DELTA_MOVE_OPTK

#include "../Commons.hpp"

using namespace twtjssp;

class DeltaMoveOptk{

public:
	DeltaMoveOptk();
	DeltaMoveOptk(Solution s, int tamBloco, int posNumber);
	DeltaMoveOptk(int tamBloco, int posNumber);

	Solution apply_optk_move();

	void set_solution(Solution);
	void set_tam_bloco(int);
	void set_pos_number(int);

private:
	Solution solution;
	int tamBloco;
	int posNumber;
};

#endif
