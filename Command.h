#include <string>
#include <iostream>

using namespace std;

class Command{
    private:
    string *command;
    string *effect;

    public:
    Command();
    Command(string *commandName);
    Command(string *commandName, string *effect);
    ~Command();
    void SaveEffect(string *effect);
    string* toString();
};