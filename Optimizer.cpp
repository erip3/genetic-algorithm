#include "Optimizer.h"
#include "Rule.h"
#include "Schedule.h"
#include <ctime>
#include <iostream>

using namespace std;

// Crossover function for creating new generations
//
Schedule* crossover(const Schedule* schedule1, const Schedule* schedule2) {

    Schedule* newSchedule = new Schedule;

    int randomNum = (rand() % schedule1->getNodeCount()) + 1;
    int count = 0;

    Node* currentNode1 = schedule1->getHead();
    Node* currentNode2 = schedule2->getHead();

    // Adds nodes to new schedule from schedule 1
    // Once randomNum nodes are created, adds from schedule 2
    //
    while (currentNode1 != nullptr && currentNode2 != nullptr) {

        if (count < randomNum) {
            newSchedule->copyInsert(currentNode1);
        } else {
            newSchedule->copyInsert(currentNode2);
        }

        currentNode1 = currentNode1->next;
        currentNode2 = currentNode2->next;
        count++;
    }

    return newSchedule;
}


Schedule* Optimizer::findOptimalSchedule(const string fileName) {

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

    Rule* rules[9] = {new Rule1(), new Rule2(), new Rule3(), new Rule4(), new Rule5(),
                      new Rule6(), new Rule7(), new Rule8(), new Rule9()};

    Schedule* currentSchedule;
    int generationsCreated = 1;
    int stableCount = 0;
    int bestFitness;
    int prevBest;

    Schedule* templateSchedule = new Schedule;
    templateSchedule->initializeTemplateSchedule(fileName);

    srand(time(0));

    // POPULATION_SIZE schedules are created and stored in an array
    for (int i=0; i<POPULATION_SIZE; ++i) {
        currentSchedule = new Schedule(*templateSchedule);
        currentSchedule->randomizeScheduleMeetings();

        for (Rule* rule : rules) { // Fitness for each rule is added to the schedules fitness
            rule->getFitness(currentSchedule);
        }

        schedules[i] = currentSchedule;
    }

    bestFitness = schedules[0]->getFitness();

    cout << "Generation 1 Best Fitness: " << bestFitness << endl;
    
    while (bestFitness != 0 && generationsCreated <= MAX_ITERATIONS && stableCount <= STABLE_ITERATIONS) {

        // Elite schedules added to array
        //
        for (int i=0; i<ELITE_SIZE; ++i) {
            eliteSchedules[i] = schedules[i];
        }

        // Non-Elite schedules are deleted 
        //
        for (int i=ELITE_SIZE; i<POPULATION_SIZE; ++i) {
            delete schedules[i];
        }

        // New Generation Creation
        //
        for (int i=ELITE_SIZE; i<POPULATION_SIZE; ++i) {

            int random1 = (rand() % ELITE_SIZE);
            int random2 = (rand() % ELITE_SIZE);

            while (random1 == random2) {
                random2 = (rand() % ELITE_SIZE);
            }

            currentSchedule = crossover(eliteSchedules[random1], eliteSchedules[random2]);

            // Fitness for each rule is added to the schedules fitness
            //
            for (Rule* rule : rules) {
                rule->getFitness(currentSchedule);
            }

            // The schedule is inserted into the array based on fitness
            //
            bool inserted = false;
            int s = 0;

            while (!inserted && s < i) {

                if (schedules[s]->getFitness() >= currentSchedule->getFitness()) {

                    inserted = true;

                    for (int k=i; k > s; --k) {
                        schedules[k] = schedules[k-1];
                    }

                    schedules[s] = currentSchedule;
                }

                s++;
            }

            if (!inserted) {
                schedules[i] = currentSchedule;
            }
        }

        generationsCreated++;

        prevBest = bestFitness;
        bestFitness = schedules[0]->getFitness();

        if (bestFitness == prevBest) {
            stableCount++;
        } else {
            stableCount = 0;
        }

        cout << "Generation " << generationsCreated <<  " Best Fitness: " << bestFitness << endl;
    }

    return schedules[0];
}
