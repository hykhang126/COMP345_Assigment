#pragma once
#include <list>
#include <vector>
#include <string>
#include <iostream>

#include "Map.h"
#include "Orders.h"
#include "Cards.h"

using namespace std;

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
        int* reinforcement;

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
        void issueOrder();
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
        //setters
        void setTerritoryCollection(vector <Territory*>);
        void setReinforcement(int number);
};