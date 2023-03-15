//
// Created by Eric on 3/14/2023.
//

#ifndef COMP345_ASSIGMENT1_LOGGINGOBSERVER_H
#define COMP345_ASSIGMENT1_LOGGINGOBSERVER_H
#include <list>
#include <vector>
// Abstract class, no need for constructors or operators
class ILoggable {
public:
    virtual std::string stringToLog() = 0;
};


class Subject;
// Abstract class again
class Observer {
public:
    Observer();
    ~Observer();
    virtual void update(ILoggable*) = 0;
};

// No pointers or members in this class, copy and assignment constructors are as default
class LogObserver : Observer {
public:
    LogObserver();
    ~LogObserver() = default;
    void update(ILoggable*) override;
    friend std::ostream& operator<<(std::ostream &out, const LogObserver &logObserver);
    LogObserver(const LogObserver&) = default;
    LogObserver& operator =(const LogObserver&) = default;
};

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

extern LogObserver* gameLogObserver;

#endif //COMP345_ASSIGMENT1_LOGGINGOBSERVER_H
