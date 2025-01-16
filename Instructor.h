#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "Meeting.h"
#include <string>
#include <vector>

using namespace std;

class Instructor {
private:
    string name;                         // The instructor's name.
    static const int WEEKDAYS = 5;
    vector<Meeting*> meetings[WEEKDAYS]; // Array of vectors containing meetings
public:
    Instructor();
    Instructor(const Instructor &other);
    ~Instructor();

    void setName(string name);

    void addMeeting(Meeting* meeting);

    // Returns the meeting count on a specified day
    int getMeetingCount(int day); 
};

#endif