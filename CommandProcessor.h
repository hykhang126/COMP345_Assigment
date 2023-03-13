#include <vector>
#include "Command.h"
#include "GameEngine.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class CommandProcessor
{
    private:
    vector<Command*> * commandList;
    void ReadCommand();

    public :
    CommandProcessor();
    ~CommandProcessor();
    vector<Command*> GetCommand();
    bool Validate(State * currentState, Command * command);
    void SaveCommand(Command * commandName);

};