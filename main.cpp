#include <iostream>
#include "Schedule.h"
#include "Optimizer.h"

using namespace std;

int main() {

    Optimizer optimizer;
    Schedule* schedule = optimizer.optimizeSchedule();

    cout << endl;
    cout << "Optimal Schedule: " << endl;

    schedule->display();

    cout << "fitness : " << schedule->getFitness() << endl;
    cout << endl;

    return 0;
}
