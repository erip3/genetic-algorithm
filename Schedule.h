#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Section.h"
#include "Meeting.h"
#include "Instructor.h"
#include <unordered_map>


struct Node {
    Node* next;       // Pointer to the next node on the schedule.
    Section* section; // This node's section.
};

// This class represents a weekly schedule of classes. 
//
class Schedule {
private:
    Node* head;                // The first node on the schedule.
    int nodeCount = 0;         // The number of nodes on the schedule, initially 0.
    int fitness = 0;           // The fitness value of the schedule, initially 0.
    unordered_map<string, Instructor*> instructors; // Hashmap of instructors, indexed by instructor name
    int instructorCount = 0;   // Number of instructors currently on the schedule.
    
public:
    Schedule();
    Schedule(const Schedule& other);
    ~Schedule();

    // Gets the number of nodes on a schedule.
    int getNodeCount() const;

    // Gets a pointer to the first node on the schedule.
    Node* getHead() const;

    // Creates a basic template schedule using a specified text file.
    void initializeTemplateSchedule(const string fileName);

    // Randomly assign meetings to each section in the schedule.
    void randomizeScheduleMeetings();

    // Copies a node and inserts it into the schedule.
    void copyInsert(const Node* node);

    // Gets the number of instructors on the schedule.
    int getInstructorCount() const;

    // Gets the fitness value of the schedule.
    int getFitness() const;

    // Updates the fitness value of the schedule.
    void updateFitness(int addedValue);

    // Outputs all of a schedule's meetings to the user.
    void display() const;
};

#endif 
