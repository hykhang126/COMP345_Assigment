#pragma once
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

class Deck;
class Territory;
class Hand;
class OrdersList;
class Player;

class Player{
    private :
        string* name;
        Hand* hand;
        vector<Territory*>* tCollection;
        OrdersList* listOfOrders;

        vector<Territory*>* territoriesToAttack;
        vector<Territory*>* territoriesToDefend;
        int* reinforcement;
        vector<Player*>* negotiating;
        bool* hasConquered;


    public :
        //Basic constructor
        Player();
        //Contructor taking in all attributes as params
        Player(string* name, vector<Territory*> tCollection, Hand* hand, OrdersList* listOfOrders);
        //Copy constructor
        Player(const Player& p);
        //Destructor
        ~Player();
        //returns a list of territories that are to be defended
        vector<Territory*>* toDefend();
        //returns a list of territories that are to be attacked
        vector<Territory*>* toAttack();
        //creates an order object and adds it to the list of orders
        void issueOrder(vector<Player*>* gamePlayers, Deck* deck);
        //assignment operator
        Player& operator =(const Player& e);
        //stream insertion operator
        friend ostream& operator<<(ostream& out, const Player& player);
        //getters
        string* getName();
        Hand* getHand();
        OrdersList* getOrdersList();
        vector<Territory*>* getTerritoryCollection();
        int* getReinforcement();
        vector<Player*>* getNegotiating();
        bool* getHasConquered();
        //setters
        void setTerritoriesToAttack();
        void setTerritoriesToDefend();
  
        bool hasCardInHand(string cardName);

        void setTerritoryCollection(vector <Territory*>*);
        void setReinforcement(int* number);
        void setName(string name);
        void setNegotiating(vector<Player*>* list);
        void setHasConquered(bool* check);

};