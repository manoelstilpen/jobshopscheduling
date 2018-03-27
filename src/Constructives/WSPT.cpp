#include "WSPT.hpp"

WSPT::WSPT(double _alpha) : Constructive(_alpha) {

}

void WSPT::print_method_informations(){
    cout << "=========================================================================================" << endl;
	cout << " -> CONSTRUCTIVE WSPT <-" << endl;
    cout << "ALPHA: " << this->alpha << endl;
}

float WSPT::define_priority(Schedule op){
    return (float) -(float(ProblemInstance::getPriorityFromJob(op.job)) / float(op.time_execution));
}

/*float WSPT::valor_grasp(const float& min, const float& max){
    return (float) (max + alpha*(min-max));
}*/