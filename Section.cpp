#include "Section.h"

#include <iostream>
#include <string>


Section::Section() {

    identifier = "";
    instructor = "";
    meetingCount = 0;
    meetings = new Meeting*[3];
    
}


// Copy constructor for section
//
Section::Section(const Section &section) {

    identifier = section.identifier;
    instructor = section.instructor;
    meetingCount = section.meetingCount;
    meetings = new Meeting*[3];

    for (int i=0; i<meetingCount; ++i) {

        meetings[i] = new Meeting(*section.meetings[i]);

    }

}


// Adds a meeting to the section
//
void Section::addMeeting(Meeting* newMeeting) {

    meetings[meetingCount] = newMeeting;
    ++meetingCount;

}


// Used to convert from military to civilian time for display purposes
//
string MtoCtime(int time) {

    string newTime;

    if (time > 12) {

        time -= 12;
        newTime = to_string(time) + " PM";

    } else if (time == 12) {

        newTime = to_string(time) + " PM";

    } else if (time == 0) {

        time += 12;
        newTime = to_string(time) + " AM";

    } else {

        newTime = to_string(time) + " AM";

    }

    return newTime;

}


// Displays all meeting from the section
//
void Section::displayMeetings() {

    for (int i=0; i<meetingCount; ++i) {

        cout << meetings[i]->getDay() << " : " << 
        MtoCtime(meetings[i]->getStartTime()) << " - " << MtoCtime(meetings[i]->getStopTime()) << endl;

    }

}


// Returns the array of meetings
//
Meeting** Section::getMeetings() {

    return meetings;

}


// Returns the meeting count
//
int Section::getMeetingCount() {

    return meetingCount;

}


// Sets identifier for the section 
//
void Section::setIdentifier(string newIdentifier) {

    identifier = newIdentifier;

}


// Sets the instructor for the section
//
void Section::setInstructor(string newInstructor) {

    instructor = newInstructor;

}


// Returns the identifier of the section
//
string Section::getIdentifier() {

    return identifier;

}


// Returns the instructor of the section
//
string Section::getInstructor() {

    return instructor;

}