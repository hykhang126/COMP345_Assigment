#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;
int main() {
    Map* map;
    MapLoader loader;
    map = loader.loadMapFromFile("france.txt");

    Hand *hand = new Hand();
    string *name = new string("Example Player");
    OrdersList *orderList = new OrdersList();
    //Create territories
    Territory *t1 = map->getTerritoryByIndex(0);
    Territory *t2 = map->getTerritoryByIndex(1);
    Territory *t3 = map->getTerritoryByIndex(2);
    vector<Territory*>* collection = new vector<Territory*>{t1, t2, t3};

    Player *player1 = new Player(name, collection, hand, orderList);

}
