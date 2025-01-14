#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Rule.h"
#include "Schedule.h"
#include "Meeting.h"

// This class is used to create generations of schedules, evaluating each
// generation against a set of rules to find the optimal schedule.
// 
class Optimizer {
public:

    // Creates generations of schedules. Evaluates each schedule against the rules
    // and assigns a fitness value to each. Generation continues until 
    // MAX_ITERATIONS number of generations have been created or STABLE_ITERATIONS 
    // number of generations have had no lowering of fitness values.
    //
    // Return:
    //    Pointer to a schedule with the lowest fitness value.
    //
    static Schedule* findOptimalSchedule(const string fileName); 
};

#endif
