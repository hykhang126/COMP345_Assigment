#include <vector>
#include "Command.h"
#include "GameEngine.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#ifndef COMMPROC_H
#define COMMPROC_H
using namespace std;

class CommandProcessor: public Subject, public ILoggable
{
    private:
    vector<Command*> * commandList;
    void ReadCommand();

    public :
    CommandProcessor();
    ~CommandProcessor();
    vector<Command*> GetCommand();
    bool Validate(State * currentState, Command * command);
    void SaveCommand(Command * commandName);

    string stringToLog() override;
};

#endif