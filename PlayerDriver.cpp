#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;
int main() {
    string playerName = "Example Player";
    vector<Territory*> tCollection;
    Hand hand;
    OrdersList listOfOrders;

    Player player1(&playerName, tCollection, &hand, &listOfOrders);
    cout << "Player name: " << *player1.getName() << endl;

    vector<Territory*>* defending = player1.toDefend();
    cout << "Defending territories:" << endl;
    for (auto territory : *defending) {
        cout << "\tTerritory name: " << territory->getName() << endl;
    }

    vector<Territory*>* attacking = player1.toAttack();
    cout << "Attacking territories:" << endl;
    for (auto territory : *attacking) {
        cout << "\tTerritory name: " << territory->getName() << endl;
    }

    Player player2(player1);
    cout << "Copied player name: " << *player2.getName() << endl;

    return 0;
}
