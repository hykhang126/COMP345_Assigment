#include <iostream>
#include <fstream>
#include "LoggingObserver.h"

using namespace std;

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


void Subject::notify(ILoggable * subject) {
    for(auto& observer : *observersList){
        observer -> update(subject);
    }
}

void Subject::attach(LogObserver * observer) {
    observersList->push_back(observer);
}

void Subject::detach(LogObserver * logObserver) {
    observersList->remove(logObserver);
}

Subject::Subject() {
    observersList = new list<LogObserver*>;
}

Subject::~Subject() {
    for (auto p : *observersList)
    {
        delete p;
        p = nullptr; // taking care of dangling, just in case
    }
    observersList->clear(); // clearing the list.
    delete(observersList); // Since list is a pointer to a vector, we delete it too
    observersList=nullptr;
}

std::ostream &operator<<(ostream &out, const Subject &subject) {
    out << "Observers are: \n";
    for (auto& observer : *subject.observersList)
    {
        out << observer << "\n";
    };
    return out;
}

Subject::Subject(const Subject &subject) {
    this->observersList = new std::list<LogObserver*> {};
    for (auto Observer : *subject.observersList)
    {
        auto *logObserverDeepCopy = new LogObserver(*Observer);
        this->observersList->push_back(logObserverDeepCopy);
    };
}

Subject &Subject::operator=(const Subject &subject) {
    this->observersList = new std::list<LogObserver*> {};
    for (auto Observer : *subject.observersList)
    {
        auto *logObserverDeepCopy = new LogObserver(*Observer);
        this->observersList->push_back(logObserverDeepCopy);
    };
    return *this;
}

Observer::Observer() = default;

Observer::~Observer() = default;

LogObserver* gameLogObserver = new LogObserver();