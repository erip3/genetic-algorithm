#include "Section.h"
#include <iostream>
#include <string>

// Used to convert from military to civilian time for display purposes
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


Section::Section() 
    : identifier(""), instructor(""), meetings(new Meeting*[3]), meetingCount(0) {}

Section::Section(const Section &section) {
    identifier = section.identifier;
    instructor = section.instructor;
    meetingCount = section.meetingCount;
    meetings = new Meeting*[3];

    for (int i=0; i<meetingCount; ++i) {
        meetings[i] = new Meeting(*section.meetings[i]);
    }
}

void Section::addMeeting(Meeting* newMeeting) {
    meetings[meetingCount] = newMeeting;
    ++meetingCount;
}

void Section::displayMeetings() {

    for (int i=0; i<meetingCount; ++i) {
        cout << meetings[i]->getDay() << " : " << 
        MtoCtime(meetings[i]->getStartTime()) << " - " << MtoCtime(meetings[i]->getStopTime()) << endl;
    }
}

string Section::getIdentifier() const { return identifier; }

string Section::getInstructor() const { return instructor; }

Meeting** Section::getMeetings() const { return meetings; }

int Section::getMeetingCount() const { return meetingCount; }

void Section::setIdentifier(string newIdentifier) { identifier = newIdentifier; }

void Section::setInstructor(string newInstructor) { instructor = newInstructor; }