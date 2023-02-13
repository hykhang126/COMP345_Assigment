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

    //creating cards for hand
    Card* card1 = new Card("test card 1");
    Card* card2 = new Card("test card 2");
    vector<Card*> playerCards = {card1, card2};
    hand->setCardsInHand(playerCards);

    //Create player 1
    Player* player1 = new Player(playerName, tCollection, hand, listOfOrders);
    cout << "Player name: " << *player1->getName() << endl;

    //------------creating territories for player 1---------------------------
    int* armies1 = new int(5);
    int* pos1 = new int(1);
    string* name1 = new string("Player Territory1");
    string* name2 = new string("Player Territory2");
    //Creating continents for territories
    string* contName1 = new string("Continent1");
    string* contName2 = new string("Continent2");
    string* color1 = new string("Red");
    string* color2 = new string("Blue");
    int* point1 = new int(1);
    Continent* continent1 = new Continent(pos1, contName1, point1, color1); 
    Continent* continent2 = new Continent(pos1, contName2, point1, color2);
  
    //Creating coordinate objects for territoreis
    int* x = new int(1);
    int* y = new int(2);
    Coordinate* coordinate1 = new Coordinate(x, y);
 
    //creating territories 
    Territory* territory1 = new Territory(player1, armies1, pos1, name1, continent1, coordinate1);
    Territory* territory2 = new Territory(player1, armies1, pos1, name2, continent2, coordinate1);
   
    //setting player 1's territorry collection
    vector<Territory*> playerTerritories = {territory1, territory2};
    player1->setTerritoryCollection(playerTerritories);

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

    cout << "\nPlayer info: \n" << *player1 << endl;

    return 0;
}
