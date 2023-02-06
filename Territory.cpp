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