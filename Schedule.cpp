#include "Schedule.h"
#include "Instructor.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <ctime>
#include <unordered_map>

using namespace std;

Schedule::Schedule() : head(nullptr) {}

Schedule::Schedule(const Schedule& other) 
    : head(nullptr), nodeCount(other.nodeCount), 
    fitness(other.fitness), instructorCount(other.instructorCount) {

    Schedule* newSchedule = new Schedule;
    Node* otherCurrentNode = other.head;
    Node* currentNode = nullptr;

    if (otherCurrentNode) {
        head = new Node;
        head->section = new Section(*currentNode->section);
        head->next = nullptr;
        currentNode = head;
        otherCurrentNode = otherCurrentNode->next;

        // Copy all nodes
        while (otherCurrentNode != nullptr) {
            currentNode->next = new Node;
            currentNode = currentNode->next;
            currentNode->section = new Section(*otherCurrentNode->section);
            otherCurrentNode = otherCurrentNode->next;
        }
    }

    // Deep copy of the instructors map
    for (const auto& pair : other.instructors) {
        instructors[pair.first] = new Instructor(*pair.second);
    }
}

Schedule::~Schedule() {
    Node* currentNode = head;
    Node* previousNode;

    while (currentNode != nullptr) {
        previousNode = currentNode;
        currentNode = currentNode->next;
        delete previousNode;
    }

    for (auto& pair : instructors) {
        delete pair.second;
    }
}

Node* Schedule::getHead() const { return head; }

int Schedule::getNodeCount() const { return nodeCount; }

void Schedule::initializeTemplateSchedule(const string fileName) {

    ifstream inFS;
    inFS.open(fileName);

    Node* currentNode;
    Node* previousNode;
    Section* newSection;
    Instructor* newInstructor;

    do { // Gather information from file
        nodeCount++;
        string newIdentifier;
        string newInstructorName;

        currentNode = new Node;
        newSection = new Section;

        // Read identifier and instuctor from file, inserting into newSection
        inFS >> newIdentifier;
        newSection->setIdentifier(newIdentifier);
        inFS >> newInstructorName;
        newSection->setInstructor(newInstructorName);

        // Add instructor to instructors map if not already added
        if (!instructors.contains(newInstructorName)) {
            newInstructor = new Instructor;
            newInstructor->setName(newInstructorName);
            instructors.insert(make_pair(newInstructorName, newInstructor));
        }

        currentNode->section = newSection;
        currentNode->next = nullptr;

        // Nodes are assigned their next pointers
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

void Schedule::randomizeScheduleMeetings() {
    Node* currentNode = head;

    while (currentNode) {
        currentNode->section->addMeeting(new Meeting);
        currentNode = currentNode->next;
    }
}

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

int Schedule::getFitness() const { return fitness; }

void Schedule::updateFitness(int addedValue) { fitness += addedValue; }

int Schedule::getInstructorCount() const { return instructorCount; }
