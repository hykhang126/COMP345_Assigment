#include "Map.cpp"


int main()
{
    Map* map;
    MapLoader loader;
    map = loader.loadMapFromFile("france.txt");
    map->toString();
    map->validate();
    
}