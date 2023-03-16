#include <string>
#include <iostream>
#include "LoggingObserver.h"
#ifndef COMMANDS_H
#define COMMANDS_H
using namespace std;

class Command : public ILoggable, public Subject{
    private:
    string *command;
    string *effect;

    public:
    string stringToLog() override;
    Command();
    Command(string *commandName);
    Command(string *commandName, string *effect);

    friend ostream& operator << (ostream& out, const Command& command);
    ~Command();
    void SaveEffect(string *effect);
    string* toString();
    string getEffect();
};

#endif