#ifndef MEETING_H
#define MEETING_H

// This class represents a meeting held on a single day. The meeting has a start and stop time.
//
class Meeting {
private:

    int start; // Meeting start time; an integer between 0-23 representing the hour.
    int stop;  // Meeting end time; an integer between 0-23 representing the hour.
    char day;  // Character representing day of the week on which the meeting is held.

public:

    // Default constructor; start initializes to 8, stop to 9, and day initializes to 'M'.
    //
    Meeting();

    // 3-parameter constructor; arguments initialize day, start, and stop times.
    //
    Meeting(char initDay, int initStart, int initStop);

    // Copy constructor.
    //
    Meeting(const Meeting &meeting);


    // Sets newStart as the meeting's start time.
    //
    virtual void setStartTime(int newStart);

    // Sets newStop at the meeting's stop time.
    //
    virtual void setStopTime(int newStop);

    // Sets newDay as the meeting's day.
    //
    virtual void setDay(char newDay);


    // Returns the meeting's start time.
    //
    virtual int getStartTime();

    // Returns the meeting's stop time.
    //
    virtual int getStopTime();

    // Returns the meeting's day.
    //
    virtual char getDay();

};

#endif