#include <fstream>
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
    notify(this);
}

string* Command::toString()
{
    return command;
}

<<<<<<< HEAD
Command::Command(const Command& com)
{
    command = com.command;
    effect = com.effect;
}

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
=======
string Command::getEffect() {
    return *effect;
}

string Command::stringToLog() {
    return "LOG: Command saving effect: " + getEffect();
}

ostream &operator<<(ostream &out, const Command &command) {
    out << "Command is " << *command.command << " with effect " << *command.effect;
    return out;
}
>>>>>>> 482f441ce90b8b8dea9d1f7163223cb136ac89a0
