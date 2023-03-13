#include "Command.h"

Command::Command(string * commandName, string * effectName): command(commandName), effect(effectName){}

Command::Command(string *commandName) : Command(commandName, new string("")){};

Command::Command() : Command(new string(""), new string("")){};

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
