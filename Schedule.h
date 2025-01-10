#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Section.h"
#include "Meeting.h"

// This struct represents a node on the schedule. Each node contains a section
// and a pointer to the next node. 
//
struct Node {
    Node* next;       // Pointer to the next node on the schedule.
    Section* section; // This node's section.
};

// This struct represents an instructor.
//
struct Instructor {
    string name;                            // The instructor's name.
    Meeting** meetings[5];                  // Array of the instructor's meetings.
    int meetingCounts[5] = {0, 0, 0, 0, 0}; // The number of meetings on each day of the week.
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
    ~Schedule();

    // Gets the number of nodes on a schedule.
    //
    virtual int getNodeCount() const;

    // Gets a pointer to the first node on the schedule.
    //
    virtual Node* getHead() const;

    // Creates a random schedule from the text file "Section.txt".
    //
    virtual void initializeSchedule();

    // Copies a node and inserts it into the schedule.
    //
    // Parameters:
    //    node (Node*) - Pointer to the node to be added to the schedule.
    //
    virtual void copyInsert(const Node* node);

    // Adds a schedule's instructors to the instructors array.
    //
    virtual void initializeInstructors();

    // Returns an array containing all of a schedule's instructors.
    //
    virtual Instructor** getInstructors();

    // Gets the number of instructors on the schedule.
    //
    virtual int getInstructorCount();

    // Gets the fitness value of the schedule.
    //
    virtual int getFitness();

    // Updates the fitness value of the schedule.
    //
    // Parameters:
    //    addedValue (int) - Value added to the schedule's current fitness value.
    //
    virtual void updateFitness(int addedValue);

    // Outputs all of a schedule's meetings to the user.
    //
    virtual void display() const;
    
};

#endif 
