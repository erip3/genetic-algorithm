#include "Rule.h"
#include "Schedule.h"

using namespace std;

// Instructors cannot be in two places at once
// Add 1000000 if an instructor is scheduled to teach two sections that overlap
//
void Rule1::getFitness(Schedule* schedule) {

};


// Instructors should be expected to be on campus for at most 9 hours/day
// Add 100 for every hour an instructor needs to remain on campus past 9 hours/day
//
void Rule2::getFitness(Schedule* schedule) {

};


// Instructors who teach at or after 6pm should not need to arrive the following day before 11am:
// Add 100 for every hour an instructor needs to arrive on campus
// before 11am when they started a class at or after 6pm
//
void Rule3::getFitness(Schedule* schedule) {

}

// Avoid scheduling instructors for more than two evenings per week
// Add 50 for every day beyond two they have start a class at 6pm or later
//
void Rule4::getFitness(Schedule* schedule) {

}


// Avoid scheduling instructors for back-to-back classes
// Add 50 for every occurrence over every day of back-to-back classes for a given instructor.
//
void Rule5::getFitness(Schedule* schedule) {

}


// Avoid scheduling instructors such that they teach immediately before and after a common hour
// Add 50 for every day an instructor teaches immediately before and after common hour.
//
void Rule6::getFitness(Schedule* schedule) {

}


// Avoid scheduling an instructor for more than 3 classes on a given day
// Add 50 for every day an instructor teaches more than 3 classes
//
void Rule7::getFitness(Schedule* schedule) {

}


// Avoid scheduling an instructor to teach two 3-hour classes on a given day.
// Add 1000 for every day an instructor teaches more than one three hour class
//
void Rule8::getFitness(Schedule* schedule) {

}


// Classes should start at 8 AM at the earliest and end at 9 PM at the latest
// Add 1000 for each meeting with times not within these limits
//
void Rule9::getFitness(Schedule* schedule) {

}
