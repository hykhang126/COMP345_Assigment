#include "Territory.h"



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