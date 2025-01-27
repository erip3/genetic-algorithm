#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Rule.h"
#include "Schedule.h"
#include "Meeting.h"

// This class is used to create generations of schedules, evaluating each
// generation against a set of rules to find the optimal schedule.
// 
class Optimizer {
private: 

    static constexpr int POPULATION_SIZE = 3000; // Number of schedules in each generation.

    static constexpr int ELITE_SIZE = 250;       // Number of elite schedules per generation.
                                             // These schedules have the lowest fitness
                                             // values of their generation.

    static constexpr int MAX_ITERATIONS = 1000;  // Maximum number of generations to be 
                                             // created.

    static constexpr int STABLE_ITERATIONS = 5;  // The maximum number of times generations
                                             // can be created without the lowering of 
                                             // fitness values. New generations stop being 
                                             // created once this number is reached.
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
