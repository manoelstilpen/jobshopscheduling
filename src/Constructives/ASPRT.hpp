#include "../Commons.hpp"
#include "../Metaheuristics/Grasp.hpp"

using namespace twtjssp;

class ASPRT : public Grasp {

public:

    ASPRT(ProblemInstance instance, double _alpha = 0, bool refine=true);

    virtual float define_priority(Schedule op);
    virtual int choose_schedule();

};