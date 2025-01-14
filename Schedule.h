#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Section.h"
#include "Meeting.h"

struct Node {
    Node* next;       // Pointer to the next node on the schedule.
    Section* section; // This node's section.
};

struct Instructor {
    string name;                            // The instructor's name.
    Meeting** meetings[5];                  // Array of the instructor's meetings.
    int meetingCounts[5] = {0, 0, 0, 0, 0}; // The number of meetings on each weekday.
                                            // All counts are initially 0.
};

// This class represents a weekly schedule of classes. 
//
class Schedule {
private:
    Node* head;                // The first node on the schedule.
    int nodeCount = 0;         // The number of nodes on the schedule, initially 0.
    int fitness = 0;           // The fitness value of the schedule, initially 0.
    static const int STEP = 5; // Initial size of the instructors array. Each time the array 
                               // becomes full, this number of spaces will be added.

    Instructor** instructors;  // Array containing pointers to each instructor.
    int instructorCount = 0;   // Number of instructors currently on the schedule.
    
public:
    Schedule();
    Schedule(const Schedule* schedule);
    ~Schedule();

    // Gets the number of nodes on a schedule.
    int getNodeCount() const;

    // Gets a pointer to the first node on the schedule.
    Node* getHead() const;

    // Creates a random schedule from the text file "Section.txt".
    void initializeSchedule(const string fileName);

    // Copies a node and inserts it into the schedule.
    void copyInsert(const Node* node);

    // Adds a schedule's instructors to the instructors array.
    void initializeInstructors();

    // Returns an array containing all of a schedule's instructors.
    Instructor** getInstructors();

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
