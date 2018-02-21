#include "WSPT.hpp"

WSPT::WSPT(){

}

WSPT::WSPT(ProblemInstance p, double _alpha) : Constructive(p, _alpha) {

}

void WSPT::print_method_informations(){
    cout << "=========================================================================================" << endl;
	cout << " -> CONSTRUCTIVE WSPT <-" << endl;
    cout << "ALPHA: " << this->alpha << endl;
}

float WSPT::define_priority(Schedule op){
    return (float) -(float(instance.get_vec_priorities()[op.job]) / float(op.time_execution));
}

int WSPT::choose_schedule(const ScheduleMatrix& jobs_temp, const vector<int>& restricts){
    
    return rand() % restricts.size();
}

/*float WSPT::valor_grasp(const float& min, const float& max){
    return (float) (max + alpha*(min-max));
}*/