#include "CommandProcessor.h"

CommandProcessor::CommandProcessor()
{

    this->commandList = new vector<Command*> {};
    cout << "Please input command:" << endl;
    cout << "(include \"-console\" if entering manually.)" <<endl;
    cout << "(include \"-file <filename>\" if import list of commands by text file.)" <<endl;

    string mode = "";
    cin >> mode;
    if(mode == "-console")
    {
        cout << "Please enter commands' name seperated by new line: " <<endl;
        cout << "Finish entering by state \"done\"" << endl;
        string command = "";
        while(command != "done")
        {
            Command * com = new Command(new string(command));
            this->SaveCommand(com);
        }
    }
    else{
        std::vector<std::string> words;
        std::istringstream iss(mode);
        std::string word;
        while (std::getline(iss, word, ' ')) {
            words.push_back(word);
        }

        if(words[0] == "-file")
        {
            try{
                string line;
                ifstream reader;
                reader.open(words[1]);
                if(reader.is_open())
                {
                    while(getline(reader,line)){
                        Command * com = new Command(new string(line));
                        this->SaveCommand(com);
                    }
                }
                reader.close();
                cout << "++++++++++++Load file into command list successfully" << endl;
                }
            catch(invalid_argument& e)
            {
                cout << "Invalid file" <<endl;
            }
        }
        else{
            cout << "invalid command -> program terminated." <<endl;

        }
    }
}

CommandProcessor::~CommandProcessor()
{
    for(Command * cm : *commandList)
    {
        delete cm;
    }
    commandList->clear();
    delete commandList;
    cout << "Deleting command list pointer." <<endl;
}

vector<Command*> CommandProcessor::GetCommand()
{
    cout << "Debug: Showing all commands: " << endl;
    for(Command * cmd : *commandList)
    {
        cout << cmd->toString() <<endl;
    }
    return *commandList;
}

bool Validate(State *currentState, Command * com)
{
    cout << "-----------------------------\n";
    cout << "Current State and its transitions:\n - ";
    currentState->showTransitions();
    cout << "Your command: " << *(com->toString());
    cout << endl;

    vector<Transition*> currTransitions = currentState->getTransitions();
    for (int i = 0; i < currTransitions.size(); i++)
    {
        if (currTransitions[i]->getName()->compare(*(com->toString())) == 0)
        {
            com->SaveEffect(new string("true"));
            cout << "Command Valid. Effect is saved." << endl;
            return true;
        }
    }
    com->SaveEffect(new string("false"));
    cout << "Command Invalid. Effect is saved." << endl;
    return false;
}

void CommandProcessor::SaveCommand(Command * com)
{
    this->commandList->push_back(com);
    cout << "Command " << *(com->toString()) << " is saved." <<endl;
    notify(this);
}

string CommandProcessor::stringToLog() {
    std::stringstream buffer;
    buffer << *commandList->back();
    return "LOG: saving Command to command list. " + buffer.str();}
