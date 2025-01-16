#ifndef SECTION_H
#define SECTION_H

#include "Meeting.h"
#include <string>

using namespace std;

// This class represents a section of a course.
//
class Section {
private:

    string identifier;  // Course identifier for the section.
    string instructor;  // Name of the instructor teaching the section.
    Meeting** meetings; // Array of meeting pointers for the section.
    int meetingCount;   // Number of weekly meetings for the section.

public:

    // Default constructor. The identifier and instructor are initially empty strings. 
    // MeetingCount initializes to 0.
    Section();

    // Copy constructor.
    Section(const Section &section);

    // Adds newMeeting to the meetings array.
    void addMeeting(Meeting* newMeeting);

    // Outputs all of a section's meetings to the user.
    void displayMeetings();

    // Returns an array of the section's meetings.
    Meeting** getMeetings() const;

    // Returns the number of weekly meetings.
    int getMeetingCount() const;

    // Returns the section's identifier.
    string getIdentifier() const;

    // Returns the name of the section's instructor.
    string getInstructor() const;

    // Sets newIdentifier as the section's identifier.
    void setIdentifier(string newIdentifier);

    // Sets newInstructor as the sections's instructor.
    void setInstructor(string newInstructor);
};

#endif
