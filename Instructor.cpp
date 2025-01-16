#include "Instructor.h"
#include "Meeting.h"

using namespace std;

Instructor::Instructor() {
    name = "";
}

Instructor::Instructor(const Instructor &other) : name(other.name) {
    for (int i=0; i<WEEKDAYS; ++i) {
        for (const Meeting* meeting : other.meetings[i]) {
            meetings->push_back(new Meeting(*meeting));
        }
    }
}

Instructor::~Instructor() {
    for (int i=0; i<WEEKDAYS; ++i) {
        for (const Meeting* meeting : meetings[i]) {
            delete meeting;
        }
    }
}

void Instructor::setName(string newName) {
    name = newName;
}

int Instructor::getMeetingCount(int day) {
    return meetings[day].size();
}