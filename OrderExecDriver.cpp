#include "Orders.h"

/**
 * Driver to demonstrate Order execution
*/
int main() {
    //--------------------------INITIALIZATION-------------------------------
    cout << "Initializing.................................." << endl;
    Player* player = new Player();
    Territory* terr1 = new Territory();
    terr1->setOwner(player);
    terr1->setName(new string("USA"));
    player->setReinforcement(50);
    player->setName("Steve");
    int* numReinforcement = new int(10);
    Order* order1 = new Deploy(numReinforcement, terr1, player);

    int* numAdvance = new int(5);
    Territory* terr2 = new Territory();
    terr2->setOwner(player);
    terr2->setName(new string("Canada"));
    terr1->adjacentTerritory->push_back(terr2);
    terr2->adjacentTerritory->push_back(terr1);
    Order* order2 = new Advance(numAdvance, terr1, terr2, player);

    Player* player2 = new Player();
    Territory* terr3 = new Territory();
    terr3->setArmies(new int(2));
    terr3->setName(new string("Mexico"));
    terr3->setOwner(player2);
    player2->setName("Danny");
    terr1->adjacentTerritory->push_back(terr3);
    terr3->adjacentTerritory->push_back(terr1);
    Order* order3 = new Advance(numAdvance, terr1, terr3, player);
    //-------------------------DEPLOY------------------------------------
    cout << "\nTesting out Deploy Order...................." << endl;
    order1->execute();
    //--------------------------ADVANCE----------------------------------
    cout << "\nTesting out Advance Order moving to owned target....................." << endl;
    order2->execute();
    cout << "\nTesting out Advance Order attacking enemy target....................." << endl;
    order3->execute();
}