#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;
int main() {
    //Creating attributes needed for player constructor
    string* playerName = new string("Example Player");
    vector<Territory*> tCollection = {};
    Hand* hand = new Hand();
    OrdersList* listOfOrders = new OrdersList();

    //Create player 1
    Player* player1 = new Player(playerName, tCollection, hand, listOfOrders);
    cout << "Player name: " << *player1->getName() << endl;

    //Create player 2 using copy constructor
    Player* player2 = new Player(*player1);
    cout << "\nCopied player name: " << *player2->getName() << endl;

    //Showing player 1's hand (empty)
    cout << "\nThis is player1's hand: " << *player1->getHand() << endl;
    
    //Showing player 1's orders list before and after issue order is called
    cout << "This is player1's order list: " << *player1->getOrdersList() << endl;
    player1->issueOrder();
    cout << "This is player1's hand after issue order: " << *player1->getOrdersList() << endl;

    //Calling function toDefend(), returns list of arbitrary territories
    vector<Territory*>* defending = player1->toDefend();
    cout << "Defending territories:" << endl;
    for (auto territory : *defending) {
        cout << "\tTerritory name: " << *territory->getName() << endl;
    }
    
    //Calling function toAttack(), returns list of arbitrary territories
    vector<Territory*>* attacking = player1->toAttack();
    cout << "Attacking territories:" << endl;
    for (auto territory : *attacking) {
        cout << "\tTerritory name: " << *territory->getName() << endl;
    }

    cout << "\nPlayer info: " << *player1 << endl;

    return 0;
}
