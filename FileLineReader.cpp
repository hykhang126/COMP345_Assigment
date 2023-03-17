#include "FileLineReader.h"

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