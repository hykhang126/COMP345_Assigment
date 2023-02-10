#include <iostream>
#include <fstream>
#include "Maps.cpp"
#include <vector>
#include <sstream>

class MapLoader{
    private:
        vector<string> split(const string &str, char delimiter);
        

    public:
        Maps* loadMapFromFile(string fileName);
};