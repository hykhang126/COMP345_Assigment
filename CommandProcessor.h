#include <vector>
#include "Command.cpp"
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
    Command* ReadCommand();
    void Validate(string * currentState, Command * command);


    public :
    CommandProcessor();
    ~CommandProcessor();
    CommandProcessor(const CommandProcessor&);
    CommandProcessor& operator= (const CommandProcessor&);
    void SaveCommand(Command * commandName);
    void GetCommand(string * curState);
    string stringToLog() override;
    void ShowCommandList();
};

#endif
