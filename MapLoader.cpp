#include "MapLoader.h"

vector<string> MapLoader::split(const string &str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while(getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

Maps* MapLoader::loadMapFromFile(string fileName)
{ 
    vector<Continent*> listContinent;
    static int counter = 1;
    bool continentFlag = false;
    bool countryFlag = false;
    bool borderFlag = false;
    string line;
    Maps* map = new Maps();
    ifstream reader;
    reader.open(fileName);
    if(reader.is_open())
    {
        while(getline(reader,line)){
            cout << line <<endl;
            if(line == "[continents]")
            {
                continentFlag = true;
                countryFlag = false;
                borderFlag = false;
                continue;
            }
            if(line == "[countries]")
            {
                countryFlag = true;
                continentFlag = false;
                borderFlag = false;
                continue;
            }
            if(line == "[borders]"){
                countryFlag = false;
                continentFlag = false;
                borderFlag = true;
                continue;
            }
            if(line.empty())
            {
                continentFlag= false;
                countryFlag= false;
                borderFlag = false;
                continue;
            }
            if(continentFlag)
            {
                vector<string> tokens = split(line, ' ');
                Continent* continent = new Continent(new int(counter++) ,new string(tokens[0]), new int(stoi(tokens[1])), new string(tokens[2]));
                listContinent.push_back(continent);
                cout << "======================== Continent"<<endl;
            }
            if(countryFlag)
            {
                vector<string> tokens = split(line, ' ');
                Continent* cont = listContinent[stoi(tokens[2])];
                Territory* territory = new Territory(new Player(), new int(0), new int(stoi(tokens[0])), new string(tokens[1]), cont, new Coordinate(new int(stoi(tokens[3])), new int(stoi(tokens[4]))));
                map->addTerritory(territory);
                cout << "======================== Coordinate"<<endl;
            }
            if(borderFlag)
            {
                vector<string> tokens = split(line, ' ');
                for(int i = 1 ; i < tokens.size(); i++)
                {
                    map->addEdge(map->getTerritoryByIndex(stoi(tokens[0])), map->getTerritoryByIndex(stoi(tokens[i])));
                }
                cout << "======================== border"<<endl;
            }
        }
    }
    reader.close();
    return map;
}

