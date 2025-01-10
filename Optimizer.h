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

    // Rules for an ideal schedule; see Rule class for descriptions.
    //
    Rule1 rule1;
    Rule2 rule2;
    Rule3 rule3;
    Rule4 rule4;
    Rule5 rule5;
    Rule6 rule6;
    Rule7 rule7;
    Rule8 rule8;
    Rule9 rule9;

    static const int POPULATION_SIZE = 3000; // Number of schedules in each generation.

    static const int ELITE_SIZE = 250;       // Number of elite schedules per generation.
                                             // These schedules have the lowest fitness
                                             // values of their generation.

    static const int MAX_ITERATIONS = 1000;  // Maximum number of generations to be 
                                             // created.

    static const int STABLE_ITERATIONS = 5;  // The maximum number of times generations
                                             // can be created without the lowering of 
                                             // fitness values. New generations stop being 
                                             // created once this number is reached.

    Schedule* schedules[POPULATION_SIZE];    // Array of schedules containing one
                                             // generation.

    Schedule* eliteSchedules[ELITE_SIZE];    // Array of schedules containing the 
                                             // schedules with the lowest fitness 
                                             // value in a generation
    
public:

    // Creates generations of schedules. Evaluates each schedule against the rules
    // and assigns a fitness value to each. Generation continues until 
    // MAX_ITERATIONS number of generations have been created or STABLE_ITERATIONS 
    // number of generations have had no lowering of fitness values.
    //
    // Return:
    //    Pointer to a schedule with the lowest fitness value.
    //
    Schedule* optimizeSchedule();
    
};

#endif 