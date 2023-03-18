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
    int* numReinforcement = new int(10);
    Order* order1 = new Deploy(numReinforcement, terr1, player);
    //-------------------------DEPLOY------------------------------------
    cout << "\nTesting out Deploy Order...................." << endl;
    order1->execute();
}