#include <string>
#include <iostream>
#include "LoggingObserver.h"
#ifndef COMMANDS_H
#define COMMANDS_H
using namespace std;

class Command{
    private:
    string *command;
    string *effect;

    public:
    Command();
    Command(string *commandName);
    Command(string *commandName, string *effect);
    ~Command();
    Command(const Command&);
    Command& operator= (const Command&);
    void SaveEffect(string *effect);
    string* toString();
    string* getCommandName();
    string getEffect();
};
    

#endif
