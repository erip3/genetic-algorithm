#include "Meeting.h"

using namespace std;

Meeting::Meeting() : start(8), stop(9), day('M') {}

Meeting::Meeting(int initDay, int initStart, int initStop) {
    
    if (initStop > 23) initStop = initStop % 23; // Wraparound for end times

    start = initStart;
    stop = initStop;
    day = initDay;
}

Meeting::Meeting(const Meeting &other) 
    : start(other.start), stop(other.stop), day(other.day) {}

void Meeting::setStartTime(int newStart) { start = newStart; }

void Meeting::setStopTime(int newStop) { stop = newStop; }

void Meeting::setDay(int newDay) { day = newDay; }

int Meeting::getStartTime() const { return start; }

int Meeting::getStopTime() const { return stop; }

int Meeting::getDay() const { return day; }
