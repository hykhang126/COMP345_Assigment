#include "Orders.h"

/**
 * Driver to demonstrate Order execution
*/
int main() {
    //--------------------------INITIALIZATION-------------------------------
    cout << "Initializing.................................." << endl;
    Player* player = new Player();
    Territory* terr1 = new Territory();
    vector<Territory*>* terrList = new vector<Territory*>();
    terrList->push_back(terr1);
    player->setTerritoryCollection(*terrList);
    int* numReinforcement = new int(10);
    Order* order1 = new Deploy(numReinforcement, terr1, player);
    OrdersList* list = new OrdersList();

    //-------------------------DEPLOY------------------------------------
    cout << "\nTesting out Deploy Order...................." << endl;
    order1->execute();
    list->addOrder(order1);
}