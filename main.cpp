#include <iostream>
#include <ctime>
#include "Schedule.h"
#include "Optimizer.h"

using namespace std;

int main() {

    srand(time(0));
    cout << "Finding Optimal Schedule..." << endl;
    Schedule* schedule = Optimizer::findOptimalSchedule("./resources/Sections.txt");

    cout << endl;
    cout << "Optimal Schedule: " << endl;

    schedule->display();

    cout << "fitness : " << schedule->getFitness() << endl;
    cout << endl;

    return 0;
}
