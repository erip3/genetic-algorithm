#ifndef MEETING_H
#define MEETING_H

// This class represents a meeting held on a single day. The meeting has a start and stop time.
//
class Meeting {
private:

    int start; // Meeting start time; an integer between 0-23 representing the hour.
    int stop;  // Meeting end time; an integer between 0-23 representing the hour.
    int day;  // Character representing day of the week on which the meeting is held.

public:

    // Default constructor; start initializes to 8, stop to 9, and day initializes to 'M'.
    Meeting();

    // 3-parameter constructor; arguments initialize day, start, and stop times.
    Meeting(int initDay, int initStart, int initStop);

    // Copy constructor.
    Meeting(const Meeting &meeting);

    // Sets newStart as the meeting's start time.
    void setStartTime(int newStart);

    // Sets newStop at the meeting's stop time.
    void setStopTime(int newStop);

    // Sets newDay as the meeting's day.
    void setDay(int newDay);

    // Returns the meeting's start time.
    int getStartTime() const;

    // Returns the meeting's stop time.
    int getStopTime() const;

    // Returns the meeting's day.
    int getDay() const;
};

#endif
