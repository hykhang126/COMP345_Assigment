#include <iostream>
#include <fstream>
#include "LoggingObserver.h"

using namespace std;

/*
 *
 *      ILoggable class
 *      Because it is an abstract virtual class, we will never create an instance of an ILoggable, only classes that inherit it
 *      **For class requirements however**, we will still define all the methods and operators as default
 *      Except for the stream insertion operator which we define fully
 *
 */
ILoggable::ILoggable() = default;
ILoggable::~ILoggable() = default;
std::ostream &operator<<(ostream &out, const ILoggable &ILoggable) {
    out << "ILoggable output \n";
    return out;
}

ILoggable &ILoggable::operator=(const ILoggable &) {
    return *this;
}

ILoggable::ILoggable(const ILoggable &) = default;

/*
 *
 *      Observer class
 *      Because it is an abstract virtual class, we will never create an instance of an Observer, only classes that inherit it
 *      For class requirements however, we will still define all the methods and operators as default
 *      Except for the stream insertion operator which we define fully
 *
 */
Observer::Observer() = default;

Observer::~Observer() = default;


std::ostream &operator<<(ostream &out, const Observer &observer) {
    out << "Observer output \n";
    return out;
}

Observer &Observer::operator=(const Observer &) {
    return *this;
}

Observer::Observer(const Observer &) = default;

/*
 *
 *      LogObserver class
 *      Concrete class that will be created and defined
 *      However, it has no members. Thus, most of its constructors, destructor, assignment and copy constructors are default
 *
 */

// This method is called whenever a subject notifies a change
// Inserts the subject log into a gameLog, appends to it
void LogObserver::update(ILoggable *subject) {
    ofstream logFile;
    logFile.open ("gameLog.txt", ios::app);
    logFile << subject->stringToLog() << "\n";
    logFile.close();
}

LogObserver::LogObserver() = default;

std::ostream &operator<<(ostream &out, const LogObserver &logObserver) {
    out << "LogObserver output \n";
    return out;
}

LogObserver &LogObserver::operator=(const LogObserver &) {
    return *this;
}

LogObserver::LogObserver(const LogObserver &) = default;

LogObserver::~LogObserver() = default;

/*
 *
 *      Subject class
 *      In theory, a purely Subject class will never be created, only used for implementations
 *      However, it is not an abstract class and it has members to define
 *      Thus we define appropriately methods and operators with pointers in mind
 *
 */

// Called whenever any subject needs to notify a change
// All observers attached with subject are then notified, and can perform their update action (write to log)
void Subject::notify(ILoggable * subject) {
    for(auto& observer : *observersList){
        observer -> update(subject);
    }
}

// Attach and detach. Simply add to a list of observers
void Subject::attach(LogObserver * observer) {
    observersList->push_back(observer);
}

void Subject::detach(LogObserver * logObserver) {
    observersList->remove(logObserver);
}

// Make sure to initialize the list first whenever you have a new Subject
Subject::Subject() {
    observersList = new list<LogObserver*>;
}

// Correctly deletes Subject and take care of pointers
Subject::~Subject() {
    if (observersList!=nullptr) {
        for (auto p: *observersList) {
            delete p;
            p = nullptr; // taking care of dangling, just in case
        }
        observersList->clear(); // clearing the list.
        delete (observersList); // Since list is a pointer to a vector, we delete it too
        observersList = nullptr;
    }
}

// Note all the observers that are attached
std::ostream &operator<<(ostream &out, const Subject &subject) {
    out << "Observers are: \n";
    for (auto& observer : *subject.observersList)
    {
        out << observer << "\n";
    };
    return out;
}

// Copy constructor, creating new items in heap for deep copy
Subject::Subject(const Subject &subject) {
    this->observersList = new std::list<LogObserver*> {};
    for (auto Observer : *subject.observersList)
    {
        auto *logObserverDeepCopy = new LogObserver(*Observer);
        this->observersList->push_back(logObserverDeepCopy);
    };
}

// Assignment operator, creating new items in heap for deep copy
Subject &Subject::operator=(const Subject &subject) {
    this->observersList = new std::list<LogObserver*> {};
    for (auto Observer : *subject.observersList)
    {
        auto *logObserverDeepCopy = new LogObserver(*Observer);
        this->observersList->push_back(logObserverDeepCopy);
    };
    return *this;
}

