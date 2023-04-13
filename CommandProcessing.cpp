#include "CommandProcessing.h"
<<<<<<< Updated upstream


=======
>>>>>>> Stashed changes
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
    notify(this);
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
ostream &operator<<(ostream &out,  Command &command) {
    out << "Command is " << *command.command << " with effect " << *command.effect;
    return out;
}

string Command::stringToLog() {
    return "LOG: Command saving effect: " + getEffect();
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

<<<<<<< Updated upstream
 
    //
    string s;
    stringstream ss(cmmnd);
    vector<string> v;
    while (getline(ss, s, ' ')) {
        v.push_back(s);
    }
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
    //

    if(v[0] == "tournament")
    {
        if(v[1] != "-M" || v[3] != "-P" || v[5] != "-G" || v[7] != "-D")
        {
            cout << "Invalid command in current state."<<endl;
        }
        else{
            if(stoi(v[2]) < 1 || stoi(v[2]) >5)
            {
                cout << "Map need to be between 1 to 5 maps." << endl;
            }
            else{
                if(stoi(v[4]) < 2 || stoi(v[4]) > 4)
                {
                    cout << "Need minimum 2 or maximum of 4 players." << endl;
                }
                else{
                    if(stoi(v[6]) < 1 || stoi(v[6]) > 5)
                    {   
                        cout << "Number of game need to be between 1 and 5." << endl;
                    }
                    else{
                        if(stoi(v[8]) < 10 || stoi(v[8]) > 50)
                        {
                            cout << "Number of turns need to be between 10 and 50." <<endl;
                        }
                        else
                        {
                            GameEngine::M = stoi(v[2]);
                            GameEngine::P = stoi(v[4]);
                            GameEngine::G = stoi(v[4]);
                            GameEngine::D = stoi(v[4]);
                            com->SaveEffect(new string("true"));
                            SaveCommand(com);
                            cout << "Command is valid and saved.";
                        }
                    }
                }
            }
        }
    }


    if(cmmnd == "MapLoaded")
    {
        if(*currentState == "Start" || *currentState == "MapLoaded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            //delete currentState;
            *currentState = "MapLoaded";
            //currentState = new string("maploaded");
=======
    if( cmmnd.compare("loadmap") == 0 )
    {
        if(*currentState == "Start" || *currentState == "maploaded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
            delete currentState;
            currentState = new string("maploaded");
>>>>>>> Stashed changes
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

<<<<<<< Updated upstream
    if(cmmnd == "MapValidated")
=======
    if(cmmnd.compare("validatemap") == 0)
>>>>>>> Stashed changes
    {
        if(*currentState == "MapLoaded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
<<<<<<< Updated upstream
            //delete currentState;
            *currentState = "MapValidated";
            //currentState = new string("mapvalidated");
=======
            delete currentState;
            currentState = new string("MapValidated");
>>>>>>> Stashed changes
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

<<<<<<< Updated upstream
    if(cmmnd == "PlayersAdded")
=======
    if(cmmnd.compare("addplayer") == 0)
>>>>>>> Stashed changes
    {
        if(*currentState == "MapValidated" || *currentState == "PlayersAdded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
<<<<<<< Updated upstream
            //delete currentState;
            *currentState = "PlayersAdded";
            //currentState = new string("playeradded");
=======
            delete currentState;
            currentState = new string("PlayersAdded");
>>>>>>> Stashed changes
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

<<<<<<< Updated upstream

    if(cmmnd == "Start")
=======
    if(cmmnd.compare("gamestart") == 0)
>>>>>>> Stashed changes
    {
        if(*currentState == "PlayersAdded")
        {
            com->SaveEffect(new string("true"));
            SaveCommand(com);
<<<<<<< Updated upstream
            //delete currentState;
            *currentState = "AssignReinforcement";
            //currentState = new string("assignreinforcement");
=======
            delete currentState;
            currentState = new string("assignreinforcement");
>>>>>>> Stashed changes
            cout << "Valid command and transit to state: " << *currentState << endl;
        }
        else{
            cout << "Invalid command in current state." << endl;
        }
    }

<<<<<<< Updated upstream
    if(cmmnd == "Replay")
=======
    if(cmmnd.compare("replay") == 0)
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
    if(cmmnd == "Quit")
=======
    if(cmmnd.compare("quit") == 0)
>>>>>>> Stashed changes
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
    notify(this);
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

string CommandProcessor::stringToLog() {
    std::stringstream buffer;
    auto test = *commandList->back();

    auto test2 = commandList->back();
    buffer << *commandList->back();
    string wow = buffer.str();
    cout << test;
    return "LOG: saving Command to command list. " + buffer.str();
}

