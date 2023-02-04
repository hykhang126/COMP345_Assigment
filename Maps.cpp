#include "Maps.h"

Maps::Maps()
{
        addTerritory(Territory * ter);
        void addEdge(Territory *ter, Territory *edg);
        int countTerritory();
        int countEdge();
        void toString();
        Maps();
        Maps::~Maps(){
            for(auto const &pair : *map)
            {
                delete pair->first;
            }
        }
};