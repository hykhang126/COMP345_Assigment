#include "FileCommandProcessorAdapter.h"

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