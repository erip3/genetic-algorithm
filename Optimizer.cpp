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

    newSchedule->initializeInstructors();

    return newSchedule;

}


Schedule* Optimizer::optimizeSchedule() {

    Schedule* currentSchedule;

    int generationsCreated = 1;
    int stableCount = 0;
    int bestFitness;
    int prevBest;

    srand(time(0));

    // 100 schedule are created and stored in an array
    //
    for (int i=0; i<POPULATION_SIZE; ++i) {

        currentSchedule = new Schedule;
        currentSchedule->initializeSchedule();

        // Fitness for each rule is added to the schedules fitness
        //
        rule1.getFitness(currentSchedule);
        rule2.getFitness(currentSchedule);
        rule3.getFitness(currentSchedule);
        rule4.getFitness(currentSchedule);
        rule5.getFitness(currentSchedule);
        rule6.getFitness(currentSchedule);
        rule7.getFitness(currentSchedule);
        rule8.getFitness(currentSchedule);
        rule9.getFitness(currentSchedule);

        // The schedule is inserted into the array based on fitness
        //
        bool inserted = false;
        int s = 0;

        if (i == 0) {

            schedules[i] = currentSchedule;
            inserted = true;

        }

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
            rule1.getFitness(currentSchedule);
            rule2.getFitness(currentSchedule);
            rule3.getFitness(currentSchedule);
            rule4.getFitness(currentSchedule);
            rule5.getFitness(currentSchedule);
            rule6.getFitness(currentSchedule);
            rule7.getFitness(currentSchedule);
            rule8.getFitness(currentSchedule);
            rule9.getFitness(currentSchedule);

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
