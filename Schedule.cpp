#include "Schedule.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

Schedule::Schedule() {
    head = nullptr;
    instructors = new Instructor*[STEP];
}

Schedule::~Schedule() {
    Node* currentNode = head;
    Node* previousNode;

    while (currentNode != nullptr) {
        previousNode = currentNode;
        currentNode = currentNode->next;
        delete previousNode;
    }

    delete[] instructors;
}

// Returns pointer to first node
//
Node* Schedule::getHead() const {
    return head;
}

int Schedule::getNodeCount() const {
    return nodeCount;
}

/*
        // Randomly assigns meeting times to each section on the schedule
        // Case 1: MWF, Case 2: TR, Case 3
        //
        int randomTime;
        int num = (rand() % 8) + 1;

        // Chooses a time that doesn't overlap with common hour
        //
        if (num >= 4) {

            do {
                randomTime = (rand() % 24);
            } while (10 <= randomTime && randomTime <= 12);

        } else if (2 <= num <= 3) {

            do {
                randomTime = (rand() % 24);
            } while (10 <= randomTime && randomTime <= 12);

        } else {

            do {
                randomTime = (rand() % 24);
            } while (randomTime == 12);
        }

        // Randomly chooses a section type
        switch(num) {
            case 1:
                currentNode->section->addMeeting(new Meeting('M', randomTime, randomTime + 1));
                currentNode->section->addMeeting(new Meeting('W', randomTime, randomTime + 1));
                currentNode->section->addMeeting(new Meeting('F', randomTime, randomTime + 1));
                break;

            case 2:
                currentNode->section->addMeeting(new Meeting('T', randomTime, randomTime + 2));
                currentNode->section->addMeeting(new Meeting('R', randomTime, randomTime + 2));
                break;

            case 3: 
                currentNode->section->addMeeting(new Meeting('M', randomTime, randomTime + 2));
                currentNode->section->addMeeting(new Meeting('W', randomTime, randomTime + 2));
                break;

            case 4:
                currentNode->section->addMeeting(new Meeting('M', randomTime, randomTime + 3));
                break;

            case 5:
                currentNode->section->addMeeting(new Meeting('T', randomTime, randomTime + 3));
                break;

            case 6:
                currentNode->section->addMeeting(new Meeting('W', randomTime, randomTime + 3));
                break;

            case 7:
                currentNode->section->addMeeting(new Meeting('R', randomTime, randomTime + 3));
                break;

            case 8:
                currentNode->section->addMeeting(new Meeting('F', randomTime, randomTime + 3));
                break;  
        }

        // Instructor array is updated for new section addition
        //   
        instructorExists = false;

        for (int i=0; i<instructorCount; ++i) {

            // If the instructor exists, the meetings will be added to their struct
            // Otherwise, instructorExists remains false
            //
            if (currentNode->section->getInstructor() == instructors[i]->name) {

                instructorExists = true;

                tempMeetings = currentNode->section->getMeetings();
                tempMeetingCount = currentNode->section->getMeetingCount();

                // Loops through tempMeetings, adding each to the instructor's array
                //
                for (int k=0; k<tempMeetingCount; ++k) {

                    if (tempMeetings[k]->getDay() == 'M') {

                        instructors[i]->meetings[0][instructors[i]->meetingCounts[0]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[0];

                    } else if (tempMeetings[k]->getDay() == 'T') {

                        instructors[i]->meetings[1][instructors[i]->meetingCounts[1]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[1];

                    } else if (tempMeetings[k]->getDay() == 'W') {

                        instructors[i]->meetings[2][instructors[i]->meetingCounts[2]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[2];

                    } else if (tempMeetings[k]->getDay() == 'R') {

                        instructors[i]->meetings[3][instructors[i]->meetingCounts[3]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[3];

                    } else if (tempMeetings[k]->getDay() == 'F') {

                        instructors[i]->meetings[4][instructors[i]->meetingCounts[4]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[4];

                    }
                }
            }
        }

        // If the instructor doesn't exist, a new struct is created
        //
        if (!instructorExists) {

            // Expands array by STEP when necessary
            //
            if (instructorCount % STEP == 0) {

                Instructor** temp = new Instructor*[instructorCount + STEP];

                for (int q=0; q < instructorCount; ++q) {
                    temp[q] = instructors[q];
                }

                instructors = temp;
            }

            instructors[instructorCount] = new Instructor;

            for (int i=0; i<5; ++i) {
                instructors[instructorCount]->meetings[i] = new Meeting*[STEP];
            }

            instructors[instructorCount]->name = currentNode->section->getInstructor();

            tempMeetings = currentNode->section->getMeetings();

            tempMeetingCount = currentNode->section->getMeetingCount();

            // Adds meetings to the correct day array
            //
            for (int i=0; i<tempMeetingCount; ++i) {

                if (tempMeetings[i]->getDay() == 'M') {

                    instructors[instructorCount]->meetings[0][instructors[instructorCount]->meetingCounts[0]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[0];

                } else if (tempMeetings[i]->getDay() == 'T') {

                    instructors[instructorCount]->meetings[1][instructors[instructorCount]->meetingCounts[1]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[1];

                } else if (tempMeetings[i]->getDay() == 'W') {

                    instructors[instructorCount]->meetings[2][instructors[instructorCount]->meetingCounts[2]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[2];

                } else if (tempMeetings[i]->getDay() == 'R') {

                    instructors[instructorCount]->meetings[3][instructors[instructorCount]->meetingCounts[3]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[3];

                } else if (tempMeetings[i]->getDay() == 'F') {

                    instructors[instructorCount]->meetings[4][instructors[instructorCount]->meetingCounts[4]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[4];

                }
            }

            ++instructorCount;
        }
*/

// Used to create a basic schedule from sections.txt
//
void Schedule::initializeSchedule(const string fileName) {
    ifstream inFS;
    inFS.open(fileName);

    Node* currentNode;
    Section* newSection;
    Node* previousNode;

    bool instructorExists;

    Meeting** tempMeetings;
    int tempMeetingCount = 0;

    // Gathers all information from file
    //
    do {
        nodeCount++;
        string newIdentifier;
        string newInstructor;

        currentNode = new Node;

        // Reads identifier and instuctor from file, inserting into newSection
        //
        inFS >> newIdentifier;
        newSection->setIdentifier(newIdentifier);
        inFS >> newInstructor;
        newSection->setInstructor(newInstructor);

        currentNode->section = nullptr;
        currentNode->next = nullptr;

        // Nodes are assigned their next pointers
        //
        if (head == nullptr) {
            head = currentNode;
        } else {
            previousNode->next = currentNode;
        }

        previousNode = currentNode;

    } while (!inFS.fail() && !inFS.eof());

    // Checks of end of file was reached successfully
    if (!inFS.eof()) {
        cout << "Could not reach end of file." << endl;
    }
}


// Used to build the instructor array for a schedule
//
void Schedule::initializeInstructors() {

    Node* currentNode = head;
    bool instructorExists;

    Meeting** tempMeetings;
    int tempMeetingCount;

    while (currentNode != nullptr) {

        instructorExists = false;
        tempMeetingCount = 0;

        for (int i=0; i<instructorCount; ++i) {

            // If the instructor exists, the meetings will be added to their struct
            // Otherwise, instructorExists remains false
            //
            if (currentNode->section->getInstructor() == instructors[i]->name) {

                instructorExists = true;

                tempMeetings = currentNode->section->getMeetings();
                tempMeetingCount = currentNode->section->getMeetingCount();

                // Loops through tempMeetings, adding each to the instructor's array
                //
                for (int k=0; k<tempMeetingCount; ++k) {

                    if (tempMeetings[k]->getDay() == 'M') {

                        instructors[i]->meetings[0][instructors[i]->meetingCounts[0]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[0];

                    } else if (tempMeetings[k]->getDay() == 'T') {

                        instructors[i]->meetings[1][instructors[i]->meetingCounts[1]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[1];

                    } else if (tempMeetings[k]->getDay() == 'W') {

                        instructors[i]->meetings[2][instructors[i]->meetingCounts[2]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[2];

                    } else if (tempMeetings[k]->getDay() == 'R') {

                        instructors[i]->meetings[3][instructors[i]->meetingCounts[3]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[3];

                    } else if (tempMeetings[k]->getDay() == 'F') {

                        instructors[i]->meetings[4][instructors[i]->meetingCounts[4]] = tempMeetings[k];
                        ++instructors[i]->meetingCounts[4];

                    }
                }
            }
        }

        // If the instructor doesn't exist, a new struct is created
        //
        if (!instructorExists) {

            // Expands array by STEP when necessary
            //
            if (instructorCount % STEP == 0) {

                Instructor** temp = new Instructor*[instructorCount + STEP];

                for (int q=0; q < instructorCount; ++q) {
                    temp[q] = instructors[q];
                }

                instructors = temp;
            }

            instructors[instructorCount] = new Instructor;

            // Creates new meeting arrays for each day
            //
            for (int i=0; i<5; ++i) {
                instructors[instructorCount]->meetings[i] = new Meeting*[STEP];
            }

            instructors[instructorCount]->name = currentNode->section->getInstructor();

            tempMeetings = currentNode->section->getMeetings();

            tempMeetingCount = currentNode->section->getMeetingCount();

            // Adds meetings to the correct day array
            //
            for (int i=0; i<tempMeetingCount; ++i) {

                if (tempMeetings[i]->getDay() == 'M') {

                    instructors[instructorCount]->meetings[0][instructors[instructorCount]->meetingCounts[0]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[0];

                } else if (tempMeetings[i]->getDay() == 'T') {

                    instructors[instructorCount]->meetings[1][instructors[instructorCount]->meetingCounts[1]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[1];

                } else if (tempMeetings[i]->getDay() == 'W') {

                    instructors[instructorCount]->meetings[2][instructors[instructorCount]->meetingCounts[2]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[2];

                } else if (tempMeetings[i]->getDay() == 'R') {

                    instructors[instructorCount]->meetings[3][instructors[instructorCount]->meetingCounts[3]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[3];

                } else if (tempMeetings[i]->getDay() == 'F') {

                    instructors[instructorCount]->meetings[4][instructors[instructorCount]->meetingCounts[4]] = tempMeetings[i];
                    ++instructors[instructorCount]->meetingCounts[4];

                }
            }

            ++instructorCount;
        }

        currentNode = currentNode->next;
    }
}


// Displays all sections of a schedule
//
void Schedule::display() const {
    Node* currentNode = head;
    cout << endl;

    while (currentNode != nullptr) {
        cout << currentNode->section->getIdentifier() << " " << currentNode->section->getInstructor() << endl;
        currentNode->section->displayMeetings();
        cout << endl;

        currentNode = currentNode->next;
    }
}

// Copies a node and inserts it into the schedule
//
void Schedule::copyInsert(const Node* node) {

    Node* nodeCopy = new Node;
    Node* currentNode = head;

    bool inserted = false;

    nodeCopy->next = nullptr;
    nodeCopy->section = new Section(*(node->section));

    if (currentNode == nullptr) {
        head = nodeCopy;
    } else {

        while (!inserted) {
            
            if (currentNode->next == nullptr) {
                currentNode->next = nodeCopy;
                inserted = true;
            }

            currentNode = currentNode->next;
        }
    }

    ++nodeCount;
}

int Schedule::getFitness() const {
    return fitness;
}

void Schedule::updateFitness(int addedValue) {
    fitness += addedValue;
}

// Returns an array of instructors for a schedule
//
Instructor** Schedule::getInstructors() {
    return instructors;
}

int Schedule::getInstructorCount() const {
    return instructorCount;
}
