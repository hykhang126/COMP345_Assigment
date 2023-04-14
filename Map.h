
#ifndef MYHEADER_H
#define MYHEADER_H
#pragma once
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
#include <queue>
#include "Player.h"

using namespace std;

class Player;

//Declaration of Continent class
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
        Continent();
        string toString();
        Continent& operator= (const Continent &src);
        friend ostream& operator<< (ostream &os, const Continent &cont);
};

//Declaration of Coordinate class
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
        Coordinate();
        friend ostream& operator<< (ostream& output, Coordinate const &cor);
        Coordinate& operator= (Coordinate const &cor);
};

//Declaration of Territory class
class Territory{
    private:
        int* position;
        Player *owner;
        int *armies;
        string* name;
        Continent* continent;
        Coordinate* coordinate;
       

    public:
        vector<Territory*>* adjacentTerritory = new vector<Territory*>();
        Coordinate* getCoordinate();
        Continent* getContinent();
        string* getName();
        Player* getOwner();
        int * getArmies();
        void setOwner( Player *player);
        void setArmies( int *armies);
        void setName(string *name);
        void setAdjacentTerritory(vector<Territory*>* adj);
        Territory(Player *player, int *armies, int* pos, string* nm, Continent* cont, Coordinate* cor);
        ~Territory();
        string toString();
        int getPosition();
        friend ostream& operator<< (ostream& os, Territory const &ter);
        Territory& operator= (const Territory &ter);
        Territory(Territory const &ter);
        Territory();
        bool operator < (const Territory& ter) const;
};

//Declaration of Map class
class Map{
    private :
        map<Territory*, list<Territory*>*>* maps;
        vector<Continent*>* continentList;

    public :
        void addTerritory(Territory * ter);
        void addEdge(Territory *ter, Territory *edg);
        int countTerritory();
        int countTotalEdge();
        void toString();
        Territory* getTerritoryByIndex(int i);
        ~Map();
        void validate();
        Map();
        Map(map<Territory*, list<Territory*>*>* map, vector<Continent*>* continents);
        bool BFS();
        void setContinentList(vector<Continent*>*);
        vector<Continent*>* getContinentList();
        void BFSSubGraph();
        void showAllCoutry();
        void showAllBorder();
        void showAllContinent();
        list<Territory*> * getAdjacentTerritory(Territory * source);
};

//Declaration of MapLoader class
class MapLoader{
    private:
   
        vector<string> split(const string &str, char delimiter);
    public:
        Map* loadMapFromFile(string fileName);
};

#endif // MYHEADER_H