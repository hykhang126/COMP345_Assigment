#include "Map.h"

//definition of Player class
Player::Player()
{}

//definition of Map class
void Map::addTerritory(Territory *ter)
{
    maps->insert(pair<Territory*, list<Territory*>*>(ter, new list<Territory*>));
}   

void Map::addEdge(Territory * ter, Territory* edg)
{
    (*maps)[ter]->push_back(edg);
}

Map::Map()
{
    maps = new map<Territory*,list<Territory*>*>();
    continentList = new vector<Continent*>();
}

int Map::countTotalEdge()
{
    int counter = 0;
    for(const auto &ter : *maps)
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
    for(const auto &ter : *maps)
    {
        counter++;
    }
    return counter;
}

Map::~Map(){
    for(auto const &pair: *maps)
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
    for(const auto &ter : *maps)
    {
         cout << *ter.first->getName() << ": [";
        for(const auto &element : *ter.second)
        {
            cout << *element->getName()<<", ";
        }
        cout << "]"<<endl;
    }
}

void Map::setContinentList(vector<Continent*>* src)
{
    continentList = src;
}

Territory* Map::getTerritoryByIndex(int i)
{
    for(const auto &pair : *maps)
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
    cout <<endl << "4.1 - Checking if the graph is a connected graph?" << endl;
    if(BFS())
    {
        cout << "Yes, the graph is connected." <<endl;
    }
    else{
        cout << "No, the graph is not a connected graph." << endl;
    }
    cout << endl << "4.2 - Checking if sub-graph continent is a connected graph?" << endl;
    BFSSubGraph();
    cout <<endl<< "4.3 - Checking every country belongs to only one continent by showing Territory and its continent:" << endl;
    for(map<Territory*,list<Territory*>*>::iterator it = maps->begin(); it != maps->end(); ++it)
    {
        cout << "[Country]: " << *(*it).first->getName() << " in [Continent]: " << *(*it).first->getContinent()->getName() << endl;
    }
}

vector<Continent*>* Map::getContinentList()
{
    return continentList;
}

void Map::showAllCoutry()
 {
    int counter = 1;
    cout << "Showing all countries: " <<endl;
    for(map<Territory*,list<Territory*>*>::iterator it = maps->begin(); it != maps->end(); ++it)
    {
        cout << counter++ << " " <<  *(*it).first->getName()<< endl;
    }
 }

void Map::showAllBorder(){
    cout << "Showing all borders: " <<endl;
    int counter = 1;
    for(map<Territory*,list<Territory*>*>::iterator it = maps->begin(); it != maps->end(); ++it)
    {
        cout << counter++ <<  "[Country]: " <<  *(*it).first->getName()<< "[borders: ] " ;
        for(list<Territory*>::iterator itt = (*it).second->begin(); itt != (*it).second->end(); ++itt)
        {
            cout << *(*itt)->getName() << ", ";
        }
        cout << endl;
    }
}

void Map::showAllContinent()
{
    int counter = 1;
    cout << "Showing all continents: " <<endl;
    for(vector<Continent*>::iterator it = continentList->begin(); it != continentList->end(); ++it)
    {
        cout << counter++ <<  "[Continent]: " << *(*it)->getName() <<endl;
    }
}

void Map::BFSSubGraph() {
    for (vector<Continent*>::iterator it = getContinentList()->begin(); it != getContinentList()->end(); ++it)
    {
        bool flag = false;
        set<Territory*> continent_territories;
        for (auto const& [ter, edges] : *maps) {
            if (ter->getContinent()->getName() == (*it)->getName()) {
                continent_territories.insert(ter);
            }
        }
        if (continent_territories.empty()) {
            flag = true;
        }
        Territory* start_territory = *continent_territories.begin();
        set<Territory*> visited_territories;
        queue<Territory*> territory_queue;
        territory_queue.push(start_territory);
        while (!territory_queue.empty()) {
            Territory* current_territory = territory_queue.front();
            territory_queue.pop();
            visited_territories.insert(current_territory);
            for (auto const& edge : *(maps->at(current_territory))) {
                if (continent_territories.count(edge) > 0 && visited_territories.count(edge) == 0) {
                    territory_queue.push(edge);
                }
            }
        }
        cout << "[Continent] " << *(*it)->getName() ;
        if(flag || visited_territories.size() == continent_territories.size())
        {
            cout << " is a connected sub-graph." << endl;
        }
        flag = false;
        
    }
}


bool Map::BFS() {
    if (maps->empty()) {
        return false;
    }
    Territory* start_territory = maps->begin()->first;
    vector<bool> visited(maps->size(), false);
    queue<Territory*> q;
    q.push(start_territory);
    visited[0] = true;
    int visited_count = 1;
    while (!q.empty()) {
        Territory* t = q.front();
        q.pop();
        for (Territory* neighbor : *((*maps)[t])) {
            auto it = maps->find(neighbor);
            if (it != maps->end()) {
                int index = distance(maps->begin(), it);
                if (!visited[index]) {
                    visited[index] = true;
                    visited_count++;
                    q.push(neighbor);}
                }}}
    return visited_count == maps->size();
 }


//Definition Continent class
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

//Definition of Territory class
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

//Definition of Coordinate class
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

//Definition of MapLoader class
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
    try{
    vector<Continent*> *listContinent = new vector<Continent*>();
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
                if(tokens.size() < 3)
                {
                    cout <<endl << "Invalid map." ;
                    return nullptr;
                }
                int temp = stoi(tokens[1]);
                Continent* continent = new Continent(new int(counter) ,new string(tokens[0]), new int(stoi(tokens[1])), new string(tokens[2]));
                listContinent->push_back(continent);
                cout << "Adding Continent"<< *continent->getPosition() <<endl;
                counter++;
            }
            if(countryFlag)
            {
                vector<string> tokens = split(line, ' ');
                cout << line << tokens.size();
                if(tokens.size() != 5)
                {
                    cout <<endl << "Invalid map."  ;
                    return nullptr;
                }
                Continent* cont = (*listContinent)[stoi(tokens[2])-1];
                Territory* territory = new Territory(new Player(), new int(0), new int(stoi(tokens[0])), new string(tokens[1]), cont, new Coordinate(new int(stoi(tokens[3])), new int(stoi(tokens[4]))));
                map->addTerritory(territory);
                cout << "Added Country"<<endl;
            }
            if(borderFlag)
            {
                vector<string> tokens = split(line, ' ');
                int temp = stoi(tokens[0]);
                for(int i = 1 ; i < tokens.size(); i++)
                {
                    map->addEdge(map->getTerritoryByIndex(stoi(tokens[0])), map->getTerritoryByIndex(stoi(tokens[i])));
                }
                cout << "Added border"<<endl;
            }
        }
    }
    reader.close();
    map->setContinentList(listContinent);
    cout << "++++++++++++Load file into map successfully" << endl;
    return map;

    }
    catch(invalid_argument& e)
    {
        cout << "Invalid map" <<endl;
    }
    return nullptr;
}