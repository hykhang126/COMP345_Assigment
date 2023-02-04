#include "Territory.h"

void Territory::setArmies(int *armies)
{
    *armies = *armies;
}

void Territory::setOwner(Player *player)
{
    *owner = *player;
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
}


void Territory::toString()
{
    cout << "Player:, Armies: " << *armies; 
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