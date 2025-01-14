#include <iostream>
#include "Schedule.h"
#include "Optimizer.h"

using namespace std;

int main() {

    Schedule* schedule = Optimizer::findOptimalSchedule("Sections.txt");

    cout << endl;
    cout << "Optimal Schedule: " << endl;

    schedule->display();

    cout << "fitness : " << schedule->getFitness() << endl;
    cout << endl;

    return 0;
}
