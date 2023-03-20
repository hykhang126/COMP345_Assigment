#include "CommandProcessing.h"

//Command method implementations
//Parameterized constructors
Command::Command(string * commandName, string * effectName): command(commandName), effect(effectName){}
Command::Command(string *commandName) : Command(commandName, new string("")){};
Command::Command() : Command(new string(""), new string("")){};
//Destructor
Command::~Command(){
    cout << "command " << *command << " is deleted." <<endl;
    delete command;
    delete effect;
}
void Command::SaveEffect(string *effectName)
{
    delete effect;
    effect = NULL;
    effect = effectName;
    cout << "Saving effect " << *effect << " in command " << *command << endl;
}
string* Command::toString()
{
    return command;
}
//Copy constructor
Command::Command(const Command& com)
{
    command = com.command;
    effect = com.effect;
}
//Assignment operator
Command& Command::operator=(const Command& com)
{
    command = com.command;
    effect = com.effect;
    return *this;
}
string* Command::getCommandName()
{
    return command;
}
string Command::getEffect() {
    return *effect;
}
ostream& operator << (ostream& outPuting, Command& command)
{
    outPuting << command.toString();
    return outPuting;
}



//FileLineReader method implementations
vector<string*>* FileLineReader::ReadLineFromfile()
{
    vector<string*> *vec = new vector<string*>();
    string line;
    ifstream reader;
    reader.open(file);
    if(reader.is_open())
    {
        while(getline(reader,line)){
            vec->push_back(new string(line));        }
    }
    reader.close();
    cout << "++++++++++++Load file successfully" << endl;
    return vec;
}
FileLineReader::FileLineReader(string f)
{
    file = f;
}

FileLineReader::FileLineReader()
{
    file ="";
}

void FileLineReader::setFile(string  fileName){
    file = fileName;
}

FileLineReader::~FileLineReader()
{
    //delete some allocated memory
}

FileLineReader::FileLineReader(const FileLineReader& fileLine){
    file = fileLine.file;
}

ostream& operator << (ostream& out, FileLineReader& file)
{
    out << file.file;
    return out;
}



//FileCommandProccesorAdapter implementations
vector<Command*>* FileCommandProcessorAdapter::ReadCommand()
{
    vector<Command*>* commands = new vector<Command*>();
    vector<string*> * strings = flr->ReadLineFromfile();
    for(int i = 0 ; i < (*strings).size(); i++)
    {
        Command * cmd = new Command((*strings)[i]);
        commands->push_back(cmd);
    }
    return commands;
}
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string f)
{
    flr = new FileLineReader(f);
}
void FileCommandProcessorAdapter::GetCommand(string * curState){
    vector<Command*>* cmds = ReadCommand();
    for(int i = 0 ; i < cmds->size(); i++)
    {
        Validate(curState, (*cmds)[i]);
    }
}



//Command Processor implementations
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

ostream& operator << (ostream& outPuting, CommandProcessor& cp)
{
    for(vector<Command *>::iterator it = cp.commandList->begin(); it != cp.commandList->end(); ++it)
    {
        outPuting << *it;
    }
    return outPuting;
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
    cout << "Please enter your command: " << endl;
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