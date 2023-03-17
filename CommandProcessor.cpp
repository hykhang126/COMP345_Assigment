#include "CommandProcessor.h"

CommandProcessor::~CommandProcessor()
{
    for(Command * cm : *commandList)
    {
        delete cm;
        cout << "Deleting Command." <<endl;
    }
    commandList->clear();
    delete commandList;
    cout << "Deleting command list pointer." <<endl;
}

void CommandProcessor::Validate(string *currentState, Command * com)
{
    cout << "-----------------------------"<< endl;
    cout << "Current State is: ";
    cout << *currentState << endl;
    string cmmnd = *(com->getCommandName());
    cout << "Your command is: " << cmmnd << endl;

    if(cmmnd == "loadmap")
    {
        if(*currentState == "start" || *currentState == "maploaded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("maploaded");
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

    if(cmmnd == "validatemap")
    {
        if(*currentState == "maploaded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("mapvalidated");
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

    if(cmmnd == "addplayer")
    {
        if(*currentState == "mapvalidated" || *currentState == "playeradded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("playeradded");
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

    if(cmmnd == "gamestart")
    {
        if(*currentState == "playeradded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("assignreinforcement");
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

    if(cmmnd == "replay")
    {
        if(*currentState == "win")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("start");
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

    if(cmmnd == "quit")
    {
        if(*currentState == "win")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("exit program");
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }
}

void CommandProcessor::SaveCommand(Command * com)
{
    this->commandList->push_back(com);
    cout << "Command " << *(com->toString()) << " is saved." <<endl;
}

Command* CommandProcessor::ReadCommand(){
    cout << "Please enter your command: " <<endl;
    string * cmmndString = new string("");
    cin >> *cmmndString;
    Command* cmmnd = new Command(cmmndString);
    return cmmnd;
}

CommandProcessor::CommandProcessor(){
    commandList = new vector<Command*>();
}

CommandProcessor::CommandProcessor(const CommandProcessor& cp)
{
    commandList = cp.commandList;
}

CommandProcessor& CommandProcessor::operator= (const CommandProcessor& cp){
    commandList = cp.commandList;
    return *this;
}

void CommandProcessor::GetCommand(string * curState)
{
    Command * cmmnd = ReadCommand();
    Validate(curState, cmmnd);
}