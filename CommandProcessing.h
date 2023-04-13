#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "LoggingObserver.h"
#include "GameEngine.h"
using namespace std;

//Class Command declarations
class Command: public Subject, public ILoggable{
    private:


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
    friend ostream& operator << (ostream& outing, Command& command);
    void SaveEffect(string *effect);
    string* toString();
    string* getCommandName();
    string getEffect();
    string stringToLog() override;
    string *command;
    string *effect;
};

//Class CommandProcessor
class CommandProcessor: public Subject, public ILoggable
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
    friend ostream& operator << (ostream& outPuting, CommandProcessor&);
    string stringToLog() override;
};


//Class FileLineReader declarations
class FileLineReader{
    private:
    string file;
    public:
    FileLineReader(string);

    FileLineReader();
    void setFile(string);
    ~FileLineReader();
    FileLineReader(const FileLineReader&);
    friend ostream& operator << (ostream&, FileLineReader&);

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