#include "Maps.h"

void Maps::addTerritory(Territory *ter)
{
    maps.insert(pair<Territory*, list<Territory*>*>(ter, new list<Territory*>));
}   

void Maps::addEdge(Territory * ter, Territory* edg)
{
    (maps)[ter]->push_back(edg);
}



int Maps::countTotalEdge()
{
    int counter = 0;
    for(const auto &ter : maps)
    {
        for(const Territory *country : *ter.second)
        {
            counter++;
        }
    }
    return counter;
}

int Maps::countTerritory(){
    int counter = 0;
    for(const auto &ter : maps)
    {
        counter++;
    }
    return counter;
}

Maps::~Maps(){
    for(auto const &pair: maps )
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

void Maps::toString()
{
    for(const auto &ter : maps)
    {
         cout << *ter.first->getName() << ": [";
        for(const auto &element : *ter.second)
        {
            cout << *element->getName()<<", ";
        }
        cout << "]"<<endl;
    }
}

Territory* Maps::getTerritoryByIndex(int i)
{
    for(const auto &pair : maps)
    {
        if(pair.first->getPosition() == i)
        {
            return pair.first;
        }
    }
    return nullptr;
}