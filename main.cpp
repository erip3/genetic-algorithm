#include <iostream>

#include "Schedule.h"
#include "Optimizer.h"

using namespace std;

int main() {

    Optimizer optimizer;

    // Optimizer returns the best fit schedule using sections.txt
    //
    Schedule* schedule = optimizer.optimizeSchedule();

    cout << endl;
    cout << "World's Greatest Schedule: " << endl;

    schedule->display();

    cout << "fitness : " << schedule->getFitness() << endl;
    cout << endl;

    return 0;

}
