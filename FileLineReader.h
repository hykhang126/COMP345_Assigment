#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "CommandProcessor.cpp"

using namespace std;
class FileLineReader{
    private:
    string file;
    public:
    FileLineReader(string);
    vector<string*>* ReadLineFromfile();
};