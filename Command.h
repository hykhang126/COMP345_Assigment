#include <string>
#include <iostream>
#include "LoggingObserver.h"

using namespace std;

class Command : ILoggable, Subject{
    private:
    string *command;
    string *effect;

    public:
    string stringToLog() override;
    Command();
    Command(string *commandName);
    Command(string *commandName, string *effect);
    ~Command();
    void SaveEffect(string *effect);
    string* toString();
    string getEffect();
};