#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "LoggingObserver.h"
#ifndef COMMANDS_H
#define COMMANDS_H
using namespace std;

//Class Command declarations
class Command{
    private:
    string *command;
    string *effect;

    public:
    //Default constructor
    Command();
    //parameterized constructors
    Command(string *commandName);
    Command(string *commandName, string *effect);
    //Copy 
    Command(const Command&);
    //destructor
    ~Command();
    //Copy constructor
    Command& operator= (const Command&);
    void SaveEffect(string *effect);
    string* toString();
    string* getCommandName();
    string getEffect();
};

//Class CommandProcessor
class CommandProcessor
{
    private:
    vector<Command*> * commandList;
    Command* ReadCommand();

    protected:
    void Validate(string * currentState, Command * command);

    public :
    CommandProcessor();
    ~CommandProcessor();
    CommandProcessor(const CommandProcessor&);
    CommandProcessor& operator= (const CommandProcessor&);
    void SaveCommand(Command * commandName);
    virtual void GetCommand(string * curState);
    vector<Command*> * ReturnCommandList();
    void ShowCommandList();
    
};


//Class FileLineReader declarations
class FileLineReader{
    private:
    string file;
    public:
    FileLineReader(string);
    vector<string*>* ReadLineFromfile();
};

//Class FileCommandProcessorAdapter declaration
class FileCommandProcessorAdapter : public CommandProcessor{
    private:
    FileLineReader *flr;
    vector<Command*> * ReadCommand();
    public:
    virtual void GetCommand(string * curState);
    FileCommandProcessorAdapter(string f);
};
#endif