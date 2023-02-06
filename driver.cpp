#include "MapLoader.cpp"


int main()
{


    // Continent* cont = new Continent(new int(1), new string("Asian"), new int(3), new string("red"));
    // cout << cont->toString();
    // Coordinate* cor = new Coordinate(new int(358), new int(998));
    // cout << cor->toString();
    // Territory* ter = new Territory(new Player(), new int(333), new int(5), new string("China"), cont, cor);
    // cout << ter->toString();
    // delete ter;

    Maps* map;
    MapLoader loader;
    map = loader.loadMapFromFile("solar.txt");
    map->toString();
    
}