#include "Orders.h"

/**
 * Driver to demonstrate Order execution
*/
int main() {
    //--------------------------INITIALIZATION-------------------------------
    cout << "Initializing.................................." << endl;
    //for Deploy
    Player* player = new Player();
    Territory* terr1 = new Territory();
    vector<Territory*>* collection = new vector<Territory*>();
    terr1->setOwner(player);
    terr1->setName(new string("USA"));
    collection->push_back(terr1);
    player->setReinforcement(50);
    player->setName("Steve");
    int* numReinforcement = new int(20);
    Order* order1 = new Deploy(numReinforcement, terr1, player);

    //for advance: both territories owned by player
    int* numAdvance = new int(5);
    Territory* terr2 = new Territory();
    terr2->setOwner(player);
    terr2->setName(new string("Canada"));
    collection->push_back(terr2);
    terr1->adjacentTerritory->push_back(terr2);
    terr2->adjacentTerritory->push_back(terr1);
    Order* order2 = new Advance(numAdvance, terr1, terr2, player);

    //for advance: target belongs to enemy
    Player* player2 = new Player();
    Territory* terr3 = new Territory();
    terr3->setArmies(new int(2));
    terr3->setName(new string("Mexico"));
    terr3->setOwner(player2);
    player2->setName("Danny");
    terr1->adjacentTerritory->push_back(terr3);
    terr3->adjacentTerritory->push_back(terr1);
    Order* order3 = new Advance(numAdvance, terr1, terr3, player);

    //for airlift
    Territory* terr4 = new Territory();
    terr4->setOwner(player);
    terr4->setName(new string("France"));
    collection->push_back(terr4);
    int* numLift = new int(2);
    Order* order4 = new Airlift(numLift, terr1, terr4, player);

    //for bomb
    Territory* terr5 = new Territory();
    terr5->setOwner(player2);
    terr5->setName(new string("Spain"));
    terr5->setArmies(new int(50));
    terr4->adjacentTerritory->push_back(terr5);
    terr5->adjacentTerritory->push_back(terr4);
    Order* order5 = new Bomb(terr5, player);
    player->setTerritoryCollection(*collection);
    //-------------------------DEPLOY------------------------------------
    cout << "\nTesting out Deploy Order...................." << endl;
    order1->execute();
    //--------------------------ADVANCE----------------------------------
    cout << "\nTesting out Advance Order moving to owned target....................." << endl;
    order2->execute();
    cout << "\nTesting out Advance Order attacking enemy target....................." << endl;
    order3->execute();
    //--------------------------AIRLIFT----------------------------------
    cout << "\nTesting out Airlift Order...................." << endl;
    order4->execute();
    //--------------------------BOMB-------------------------------------
    cout << "\nTesting out Bomb Order...................." << endl;
    order5->execute();
}