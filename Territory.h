#ifndef TERRITORY_H
#define TERRITORY_H

#include "Player.h"
#include "Continent.h"
#include "Coordinate.h"
#include <iostream>
using namespace std;

class Territory{
    private:
        int* position;
        Player *owner;
        int *armies;
        string* name;
        Continent* continent;
        Coordinate* coordinate;

    public:
        Coordinate* getCoordinate();
        Continent* getContinent();
        string* getName();
        Player* getOwner();
        int* getArmies();
        void setOwner( Player *player);
        void setArmies( int *armies);
        Territory(Player *player, int *armies, int* pos, string* nm, Continent* cont, Coordinate* cor);
        ~Territory();
        void toString();
};

#endif