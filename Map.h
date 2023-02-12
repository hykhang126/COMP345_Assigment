#pragma once
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Player.h"

using namespace std;


// class Player{
//     public:
//         Player();
// };
class Player;

class Continent{
    private:
        int* position;
        string* name;
        int* point;
        string* color;

    public:
        int* getPosition();
        string* getName();
        int* getPoint();
        string* getColor();
        Continent(int* pos, string* name, int* point, string* color);
        ~Continent();
        Continent(const Continent &src);
        string toString();
        Continent& operator= (const Continent &src);
        friend ostream& operator<< (ostream &os, const Continent &cont);
};

class Coordinate{
    private:
        int* x;
        int* y;
    public: 
        int* getX();
        int* getY();
        Coordinate(int* xx, int* yy);
        ~Coordinate();
        string toString();
        Coordinate (const Coordinate& cor);
        friend ostream& operator<< (ostream& output, Coordinate const &cor);
        Coordinate& operator= (Coordinate const &cor);
};

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
        string toString();
        int getPosition();
        friend ostream& operator<< (ostream& os, Territory const &ter);
        Territory& operator= (const Territory &ter);
        Territory(Territory const &ter);
};



class Map{
    private :
        map<Territory*, list<Territory*>*> map;

    public :
        void addTerritory(Territory * ter);
        void addEdge(Territory *ter, Territory *edg);
        int countTerritory();
        int countTotalEdge();
        void toString();
        Territory* getTerritoryByIndex(int i);
        ~Map();
        void validate();
};

class MapLoader{
    private:
        vector<string> split(const string &str, char delimiter);
        

    public:
        Map* loadMapFromFile(string fileName);
};



