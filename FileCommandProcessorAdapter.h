#include "FileLineReader.cpp"


class FileCommandProcessorAdapter : public CommandProcessor{
    private:
    FileLineReader *flr;
    vector<Command*> * ReadCommand();
    public:
    virtual void GetCommand(string * curState);
    FileCommandProcessorAdapter(string f);
};