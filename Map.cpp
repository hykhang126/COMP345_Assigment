#include "Map.h"

Player::Player()
{}

void Map::addTerritory(Territory *ter)
{
    map.insert(pair<Territory*, list<Territory*>*>(ter, new list<Territory*>));
}   

void Map::addEdge(Territory * ter, Territory* edg)
{
    (map)[ter]->push_back(edg);
}



int Map::countTotalEdge()
{
    int counter = 0;
    for(const auto &ter : map)
    {
        for(const Territory *country : *ter.second)
        {
            counter++;
        }
    }
    return counter;
}

int Map::countTerritory(){
    int counter = 0;
    for(const auto &ter : map)
    {
        counter++;
    }
    return counter;
}

Map::~Map(){
    for(auto const &pair: map)
    {
        delete pair.first;
        for(auto const *ter : *pair.second)
        {
            delete ter;
        }
        delete pair.second;
    }
    cout << "delete";
} 

void Map::toString()
{
    for(const auto &ter : map)
    {
         cout << *ter.first->getName() << ": [";
        for(const auto &element : *ter.second)
        {
            cout << *element->getName()<<", ";
        }
        cout << "]"<<endl;
    }
}

Territory* Map::getTerritoryByIndex(int i)
{
    for(const auto &pair : map)
    {
        if(pair.first->getPosition() == i)
        {
            return pair.first;
        }
    }
    return nullptr;
}

void Map::validate()
{
    cout << "Checking 1-1 of Territory-Continent..." <<endl;
    for(const auto &pair : map)
    {
        cout << "Country: [" << *(pair.first->getName()) << "] : Continent: [" << *(pair.first->getContinent()->getPosition()) << "]" << endl;
    }
}


int* Continent::getPosition()
{
    return position;
}

string* Continent::getName()
{
    return name;
}

int* Continent::getPoint()
{
    return point;
}

string* Continent::getColor()
{
    return color;
}

string Continent::toString()
{
    return "position: " + to_string(*getPosition()) + ", Name: " + *getName() + ", point: " + to_string(*getPoint()) + ", color: " + *getColor();
}

Continent::Continent(const Continent &src)
{
    position = new int(*src.position);
    name = new string(*src.name);
    point = new int(*src.point);
    color = new string(*src.color);
}

Continent& Continent::operator= (const Continent &src)
{
    this->position = new int(*src.position);
    this->name = new string(*src.name);
    this->point = new int(*src.point);
    this->color = new string(*src.color);
    return *this;
}

ostream& operator<< (ostream &os, const Continent &cont)
{
    os << "position: " << to_string(*cont.position) << ", Name: " << *cont.name <<  ", point: " << to_string(*cont.point) << ", color: " << *cont.color;
    return os;
}

Continent::Continent(int* pos, string* nm, int* pts, string* clr){
    position = pos;
    name = nm;
    point = pts;
    color = clr;
}

Continent::~Continent()
{
    delete position;
    delete name;
    delete point;
    delete color;
    cout << "delete";
}


void Territory::setArmies(int *armies)
{
    armies = armies;
}

void Territory::setOwner(Player *player)
{
    owner = player;
}

int* Territory::getArmies()
{
    return armies;
}

Player* Territory::getOwner()
{
    return owner;
}

Territory::Territory(Player *pl, int *arm, int* pos, string* nm, Continent* cont, Coordinate* cor)
{
    owner = pl;
    armies = arm;
    position = pos;
    name = nm;
    continent = cont;
    coordinate = cor;
}

Territory::~Territory()
{
    delete armies;
    delete owner;
    delete position;
    delete name;
    delete continent;
    delete coordinate;
    cout << "delete";
}


string Territory::toString()
{
    return "Player:, Armies: " + to_string(*armies) + ", position: " + to_string(*position) + ", name: " + *name + ", continent: " + continent->toString() + ", Coordinate: " + coordinate->toString() ; 
}

Coordinate* Territory::getCoordinate(){
    return coordinate;
}
  
Continent* Territory::getContinent(){
    return continent;
}

string* Territory::getName(){
    return name;
}

int Territory::getPosition()
{
    return *position;
}

ostream& operator<< (ostream& os, Territory const &ter)
{
    os <<"Player:, Armies: " << to_string(*ter.armies) << ", position: " << to_string(*ter.position) << ", name: " << *ter.name << ", continent: " << ter.continent << ", Coordinate: " << ter.coordinate ; 
    return os;
}

Territory& Territory::operator= (Territory const &ter)
{
    position = new int(*ter.position);
    armies = new int(*ter.armies);
    owner = new Player();
    name = new string(*ter.name);
    continent = new Continent(*ter.continent);
    coordinate = new Coordinate(*ter.coordinate);
    return *this;
}

Territory::Territory(Territory const &ter)
{
    position = new int(*ter.position);
    armies = new int(*ter.armies);
    owner = new Player();
    name = new string(*ter.name);
    continent = new Continent(*ter.continent);
    coordinate = new Coordinate(*ter.coordinate);
}


int* Coordinate::getX()
{
    return x;
}

int* Coordinate::getY()
{
    return y;
}

Coordinate::Coordinate(int* xx, int* yy)
{
    x = xx;
    y = yy;
}

Coordinate::~Coordinate()
{
    delete x;
    delete y;
    cout<<"delete";
}

string Coordinate::toString()
{
    return "X: " + to_string(*x) + ", Y: " + to_string(*y);
}

Coordinate::Coordinate (const Coordinate& cor)
{
    this->x = cor.x;
    this->y = cor.y;
}

ostream& operator<< (ostream& output, Coordinate const &cor)
{
    output << "X: " << to_string(*cor.x) << ", Y: " << to_string(*cor.y);
    return output;
}

Coordinate& Coordinate::operator= (Coordinate const &cor){
    x = new int(*cor.x);
    y = new int(*cor.y);
    return *this;
}


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

Map* MapLoader::loadMapFromFile(string fileName)
{ 
    vector<Continent*> listContinent;
    static int counter = 1;
    bool continentFlag = false;
    bool countryFlag = false;
    bool borderFlag = false;
    string line;
    Map* map = new Map();
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
                Continent* continent = new Continent(new int(counter) ,new string(tokens[0]), new int(stoi(tokens[1])), new string(tokens[2]));
                listContinent.push_back(continent);
                cout << "======================== Continent"<< *continent->getPosition() <<endl;
                counter++;
            }
            if(countryFlag)
            {
                vector<string> tokens = split(line, ' ');
                Continent* cont = listContinent[stoi(tokens[2])-1];
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

