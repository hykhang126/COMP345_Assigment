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

    if( cmmnd.compare("loadmap") == 0 )
    {
        if(*currentState == "Start" || *currentState == "maploaded")
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

    if(cmmnd.compare("validatemap") == 0)
    {
        if(*currentState == "MapLoaded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("MapValidated");
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

    if(cmmnd.compare("addplayer") == 0)
    {
        if(*currentState == "MapValidated" || *currentState == "PlayersAdded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("PlayersAdded");
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

    if(cmmnd.compare("gamestart") == 0)
    {
        if(*currentState == "PlayersAdded")
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

    if(cmmnd.compare("replay") == 0)
    {
        if(*currentState == "Win")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("Start");
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

    if(cmmnd.compare("quit") == 0)
    {
        if(*currentState == "Win")
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

vector<Command*> * CommandProcessor::ReturnCommandList()
{
    return commandList;
}

void CommandProcessor::ShowCommandList()
{
    for(int i = 0; i < commandList->size(); i++)
    {
        cout << "Command: " << *(*commandList)[i]->toString() << endl;
    }
}

