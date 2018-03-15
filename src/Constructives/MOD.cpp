//
// Created by manoel on 04/03/18.
//

#include "MOD.hpp"

MOD::MOD(double alpha) : Constructive(alpha){

}

void MOD::print_method_informations() {
    cout << "=========================================================================================" << endl;
    cout << " -> CONSTRUCTIVE MOD <-" << endl;
    cout << "ALPHA: " << this->alpha << endl;
}

int MOD::choose_schedule(const ScheduleMatrix &jobs_temp, const vector<int> &restricts) {
    return rand() % restricts.size();
}

float MOD::define_priority(Schedule op) {
    // max (t+p(i,j), d(i,j))

    int processTime = ProblemInstance::getSchedule(op.job, op.operation).time_execution;
    int t = solution.time_can_be_alocated(op);
    int mod = t + processTime;

    int due_date = ProblemInstance::getDueTimeFromJob(op.job);
    if(due_date > mod){
        mod = due_date;
    }

    return mod;
}