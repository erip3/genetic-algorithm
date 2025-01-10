#include "Rule.h"
#include "Schedule.h"

using namespace std;

// Instructors cannot be in two places at once
// Add 1000000 if an instructor is scheduled to teach two sections that overlap
//
void Rule1::getFitness(Schedule* schedule) {

    Instructor** instructors = schedule->getInstructors();
    int instructorCount = schedule->getInstructorCount();
    Meeting* currentMeeting;
    Meeting* futureMeeting;

    // For each instructor
    for (int i=0; i<instructorCount; ++i) {

        // For each day
        for (int k=0; k<5; ++k) {

            // For each meeting on that day
            for (int j=0; j<instructors[i]->meetingCounts[k]; ++j) {

                currentMeeting = instructors[i]->meetings[k][j];

                // For all meetings after the current meeting
                for (int w=j+1; w<instructors[i]->meetingCounts[k]; ++w) {

                    futureMeeting = instructors[i]->meetings[k][w];

                    // If the meeting starts or ends during another meeting
                    if (currentMeeting->getStopTime() > futureMeeting->getStartTime() &&
                    currentMeeting->getStartTime() < futureMeeting->getStopTime()) {

                        schedule->updateFitness(1000000);
                    }
                }
            }
        }
    }
};


// Instructors should be expected to be on campus for at most 9 hours/day
// Add 100 for every hour an instructor needs to remain on campus past 9 hours/day
//
void Rule2::getFitness(Schedule* schedule) {

    Instructor** instructors = schedule->getInstructors();
    int instructorCount = schedule->getInstructorCount();

    int totalOvertimeHours = 0;
    int mondayHours;
    int tuesdayHours;
    int wednesdayHours;
    int thursdayHours;
    int fridayHours;

   for (int i=0; i<instructorCount; ++i) {

        mondayHours = 0;
        tuesdayHours = 0;
        wednesdayHours = 0;
        thursdayHours = 0;
        fridayHours = 0;

        // Adds the total hours for each professor to overtimeHours
        //
        for (int k=0; k < instructors[i]->meetingCounts[0]; ++k) {
            mondayHours += 
            instructors[i]->meetings[0][k]->getStopTime() 
            - instructors[i]->meetings[0][k]->getStartTime();
        }

        if (mondayHours > 9) {
            totalOvertimeHours += (mondayHours - 9);
        }

        for (int k=0; k < instructors[i]->meetingCounts[1]; ++k) {
            tuesdayHours += 
            instructors[i]->meetings[1][k]->getStopTime() 
            - instructors[i]->meetings[1][k]->getStartTime();
        }

        if (tuesdayHours > 9) {
            totalOvertimeHours += (tuesdayHours - 9);
        }

        for (int k=0; k < instructors[i]->meetingCounts[2]; ++k) {
            wednesdayHours += 
            instructors[i]->meetings[2][k]->getStopTime() 
            - instructors[i]->meetings[2][k]->getStartTime();
        }

        if (wednesdayHours > 9) {
            totalOvertimeHours += (wednesdayHours - 9);
        }

        for (int k=0; k < instructors[i]->meetingCounts[3]; ++k) {
            thursdayHours += 
            instructors[i]->meetings[3][k]->getStopTime() 
            - instructors[i]->meetings[3][k]->getStartTime();
        }

        if (thursdayHours > 9) {
            totalOvertimeHours += (thursdayHours - 9);
        }

        for (int k=0; k < instructors[i]->meetingCounts[4]; ++k) {
            fridayHours += 
            instructors[i]->meetings[4][k]->getStopTime() 
            - instructors[i]->meetings[4][k]->getStartTime();
        }

        if (fridayHours > 9) {
            totalOvertimeHours += (fridayHours - 9);
        }
    }

    schedule->updateFitness(totalOvertimeHours * 100);
};


// Instructors who teach at or after 6pm should not need to arrive the following day before 11am:
// Add 100 for every hour an instructor needs to arrive on campus
// before 11am when they started a class at or after 6pm
//
void Rule3::getFitness(Schedule* schedule) {

    Instructor** instructors = schedule->getInstructors();
    int instructorCount = schedule->getInstructorCount();

    Meeting* currentMeeting;
    Meeting* tomorrowMeeting;
    bool hasEveningClass = false;

    // For each instructor
    for (int i=0; i<instructorCount; ++i) {

        // For each day (besides friday)
        for (int k=0; k<4; ++k) {

            // For each meeting on that day
            for (int j=0; j<instructors[i]->meetingCounts[k]; ++j) {

                currentMeeting = instructors[i]->meetings[k][j];

                // If meeting starts in the evening
                if (currentMeeting->getStartTime() >= 18) {

                    hasEveningClass = true;

                    // Check if any meetings start before 11 AM the following day
                    for (int m=0; m<instructors[i]->meetingCounts[k+1]; ++m) {

                        tomorrowMeeting = instructors[i]->meetings[k+1][m];

                        if (tomorrowMeeting->getStartTime() < 11) {
                            schedule->updateFitness((11 - tomorrowMeeting->getStartTime()) * 100);
                        }
                    }
                }
            }
        }
    }
}

// Avoid scheduling instructors for more than two evenings per week
// Add 50 for every day beyond two they have start a class at 6pm or later
//
void Rule4::getFitness(Schedule* schedule) {

    Instructor** instructors = schedule->getInstructors();
    int instructorCount = schedule->getInstructorCount();

    Meeting* currentMeeting;
    int eveningCount;

    // For each instructor
    for (int i=0; i<instructorCount; ++i) {

        eveningCount = 0;

        // For each day
        for (int k=0; k<5; ++k) {

            // For each meeting on that day
            for (int j=0; j<instructors[i]->meetingCounts[k]; ++j) {

                currentMeeting = instructors[i]->meetings[k][j];

                // If meeting starts in the evening
                if (currentMeeting->getStartTime() >= 18) {
                    eveningCount++;
                }
            }
        }

        if (eveningCount > 2) {
            schedule->updateFitness(50 * (eveningCount - 2));
        }
    }
}


// Avoid scheduling instructors for back-to-back classes
// Add 50 for every occurrence over every day of back-to-back classes for a given instructor.
//
void Rule5::getFitness(Schedule* schedule) {

    Instructor** instructors = schedule->getInstructors();
    int instructorCount = schedule->getInstructorCount();
    Meeting* currentMeeting;

    // For each instructor
    for (int i=0; i<instructorCount; ++i) {

        // For each day
        for (int k=0; k<5; ++k) {

            // For each meeting on that day, check all subsequent meetings
            for (int j=0; j<instructors[i]->meetingCounts[k]; ++j) {

                currentMeeting = instructors[i]->meetings[k][j];

                // Checking subsequent meetings
                for (int m=j; m<instructors[i]->meetingCounts[k]; ++m) {

                    if (currentMeeting->getStopTime() == instructors[i]->meetings[k][m]->getStartTime()) {
                        schedule->updateFitness(50);
                    }
                }
            }
        }
    }
}


// Avoid scheduling instructors such that they teach immediately before and after a common hour
// Add 50 for every day an instructor teaches immediately before and after common hour.
//
void Rule6::getFitness(Schedule* schedule) {

    Node* currentNode = schedule->getHead();
    Instructor** instructors = schedule->getInstructors();
    int instructorCount = schedule->getInstructorCount();
    Meeting* currentMeeting;

    // For each instructor
    for (int i=0; i<instructorCount; ++i) {

        // For each day
        for (int k=0; k<5; ++k) {

            // For each meeting on that day, check start and stop times
            for (int j=0; j<instructors[i]->meetingCounts[k]; ++j) {

                currentMeeting = instructors[i]->meetings[k][j];

                if (currentMeeting->getStopTime() == 12 || currentMeeting->getStartTime() == 1) {
                    schedule->updateFitness(50);
                }
            }
        }
    }
}


// Avoid scheduling an instructor for more than 3 classes on a given day
// Add 50 for every day an instructor teaches more than 3 classes
//
void Rule7::getFitness(Schedule* schedule) {

    Instructor** instructors = schedule->getInstructors();
    int instructorCount = schedule->getInstructorCount();

    // For each instructor
    for (int i=0; i<instructorCount; ++i) {

        // For each day
        for (int k=0; k<5; ++k) {

            if (instructors[i]->meetingCounts[k] > 3) {
                schedule->updateFitness(50);
            }
        }
    }
}


// Avoid scheduling an instructor to teach two 3-hour classes on a given day.
// Add 1000 for every day an instructor teaches more than one three hour class
//
void Rule8::getFitness(Schedule* schedule) {

    Instructor** instructors = schedule->getInstructors();
    int instructorCount = schedule->getInstructorCount();
    Meeting* currentMeeting;
    bool threeHourMeetingExists = false;

    // For each instructor
    for (int i=0; i<instructorCount; ++i) {

        // For each day
        for (int k=0; k<5; ++k) {

            // For each meeting on that day
            for (int j=0; j<instructors[i]->meetingCounts[k]; ++j) {

                currentMeeting = instructors[i]->meetings[k][j];

                // If the total time is greater than o
                if (currentMeeting->getStopTime() - currentMeeting->getStartTime() >= 3 && threeHourMeetingExists) {
                    schedule->updateFitness(1000);
                } else if (currentMeeting->getStopTime() - currentMeeting->getStartTime() >= 3) {
                    threeHourMeetingExists = true;
                }
            }

            threeHourMeetingExists = false;
        }
    }
}


// Classes should start at 8 AM at the earliest and end at 9 PM at the latest
// Add 1000 for each meeting with times not within these limits
//
void Rule9::getFitness(Schedule* schedule) {

    Node* currentNode = schedule->getHead();
    Meeting** meetings;
    int meetingCount;

    int start;
    int stop;
    
    while (currentNode != nullptr) {

        meetings = currentNode->section->getMeetings();
        meetingCount = currentNode->section->getMeetingCount();

        // Checks if each meeting in a section starts outside of the time boundaries
        //
        for (int i=0; i<meetingCount; ++i) {

            start = meetings[i]->getStartTime();
            stop = meetings[i]->getStopTime();

            if (start < 8 || start > 20 || stop < 9 || stop > 21) {
                schedule->updateFitness(1000);
            }
        }

        currentNode = currentNode->next;
    }
}
