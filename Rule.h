#ifndef RULE_H
#define RULE_H

#include "Schedule.h"

// This class represents a condition that an ideal schedule should meet.
//
class Rule {
public:

    // Determines whether or not a schedule meets a condition. If it doesn't
    // the fitness value is increased.
    //
    virtual void getFitness(Schedule* schedule) = 0;

};

// Instructors cannot be in two places at once.
//
class Rule1 : public Rule {

    // Adds 1000000 fitness to a schedule if an instructor is 
    // scheduled to teach two sections with overlapping times.
    //
    public : virtual void getFitness(Schedule* schedule);

};

// Instructors are to be on campus for, at most, 9 hours/day.
//
class Rule2 : public Rule {

    // Adds 100 fitness to a schedule for every hour an instructor 
    // needs to remain on campus past 9 hours/day.
    //
    public : virtual void getFitness(Schedule* schedule);

};

// Instructors who teach at or after 6pm should not need to arrive the following day before 11am.
//
class Rule3 : public Rule {

    // Adds 100 fitness to a schedule for every hour an instructor 
    // needs to arrive on campus before 11am when they started a 
    // class at or after 6pm on the previous day.
    //
    public : virtual void getFitness(Schedule* schedule);

};

// Instructors should not be scheduled for more than two evenings per week.
//
class Rule4 : public Rule {

    // Adds 50 fitness to a schedule for every day beyond two 
    // that an instructor has to start a class at 6pm or later.
    //
    public : virtual void getFitness(Schedule* schedule);

};

// Instructors should not need to start a class at the time when their previous class ends.
//
class Rule5 : public Rule {

    // Adds 50 fitness to a schedule for every occurrence
    // of back-to-back classes for a given instructor.
    //
    public : virtual void getFitness(Schedule* schedule);

};

// Instructors should not teach immediately before and after common hour (12pm - 1pm).
//
class Rule6 : public Rule {

    // Adds 50 fitness to a schedule for every day an instructor 
    // teaches immediately before and after common hour.
    //
    public : virtual void getFitness(Schedule* schedule);

};

// Instructors should not be scheduled for more than 3 classes on any given day.
//
class Rule7 : public Rule {

    // Adds 50 fitness to a schedule for every day an instructor 
    // teaches more than 3 classes.
    //
    public : virtual void getFitness(Schedule* schedule);

};

// Instructors should not be scheduled to teach more than one three-hour class on a given day.
//
class Rule8 : public Rule {

    // Adds 1000 fitness to a schedule for every day an instructor 
    // teaches more than one three-hour class.
    //
    public : virtual void getFitness(Schedule* schedule);

};

// Classes should start at 8am at the earliest and end at 9pm at the latest.
//
class Rule9 : public Rule {

    // Adds 1000 fitness to a schedule for each meeting with start 
    // times earlier than 8am or stop times later than 9pm.
    //
    public : virtual void getFitness(Schedule* schedule);

};

#endif