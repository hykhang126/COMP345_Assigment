#ifndef COMP345_ASSIGMENT1_LOGGINGOBSERVER_H
#define COMP345_ASSIGMENT1_LOGGINGOBSERVER_H
#pragma once
#include <list>
#include <vector>
// Abstract class to be inherited and ask for definition of stringToLog to classes that inherit it
class ILoggable {
public:
    ILoggable();
    ~ILoggable();
    friend std::ostream& operator<<(std::ostream &out, const ILoggable &ILoggable);
    ILoggable(const ILoggable&);
    ILoggable& operator =(const ILoggable&);
    virtual std::string stringToLog() = 0;
};

// Abstract class again. Ask for definition of Observer
class Observer {
public:
    Observer();
    ~Observer();
    virtual void update(ILoggable*) = 0;
    friend std::ostream& operator<<(std::ostream &out, const Observer &observer);
    Observer(const Observer&);
    Observer& operator =(const Observer&);
};

// Concrete object but no pointers or members in this class, copy and assignment constructors are as default
// Has an update method that is called when a subject notifies it. Update should log the subject change
class LogObserver : Observer {
public:
    LogObserver();
    ~LogObserver();
    void update(ILoggable*) override;
    friend std::ostream& operator<<(std::ostream &out, const LogObserver &logObserver);
    LogObserver(const LogObserver&);
    LogObserver& operator =(const LogObserver&);
};

// To be inherited, but technically could be an object by itself. Has a list of observers
// And has appropriate subject functions
class Subject {
private:
    std::list<LogObserver*> *observersList;
public:
    void notify(ILoggable*);
    void attach(LogObserver*);
    void detach(LogObserver*);
    Subject();
    ~Subject();
    friend std::ostream& operator<<(std::ostream& out, const Subject& subject);
    Subject(const Subject&);
    Subject& operator =(const Subject&);
};


#endif //COMP345_ASSIGMENT1_LOGGINGOBSERVER_H
