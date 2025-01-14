#include "Meeting.h"

using namespace std;

Meeting::Meeting() {
    start = 8;
    stop = 9;
    day = 'M';
}

Meeting::Meeting(char initDay, int initStart, int initStop) {

    if (initStop > 23) { // Wraparound for end times 
        initStop = initStop % 23;
    }

    start = initStart;
    stop = initStop;
    day = initDay;
}

Meeting::Meeting(const Meeting &meeting) {
    start = meeting.start;
    stop = meeting.stop;
    day = meeting.day;
}

void Meeting::setStartTime(int newStart) {
    start = newStart;
}

void Meeting::setStopTime(int newStop) {
    stop = newStop;
}

void Meeting::setDay(char newDay) {
    day = newDay;
}

int Meeting::getStartTime() const {
    return start;
}

int Meeting::getStopTime() const {
    return stop;
}

char Meeting::getDay() const {
    return day;
}
