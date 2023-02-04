#include "Maps.h"

void Maps::addTerritory(Territory *ter)
{
    
}


Maps::~Maps(){
    for(auto const &pair: maps )
    {
        delete pair.first;
        for(Territory *ter : *pair.second)
        {
            delete ter;
        }
        delete pair.second;
    }
}