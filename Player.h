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
#include "PlayerStrategies.h"

using namespace std;

class Deck;
class Territory;
class Hand;
class OrdersList;
class Player;
class PlayerStrategy;

class Player{
    private :
        string* name;
        Hand* hand;
        vector<Territory*>* tCollection;
        OrdersList* listOfOrders;
        bool* wasAttacked = new bool(false);

        vector<Territory*>* territoriesToAttack;
        vector<Territory*>* territoriesToDefend;
        int* reinforcement;
        vector<Player*>* negotiating;
        bool* hasConquered;
        PlayerStrategy *playerStrategy;
        vector<Player*>* gamePlayers;

    public :
        //Basic constructor
        Player();
        //Contructor taking in all attributes as params
        Player(string* name, vector<Territory*> *tCollection, Hand* hand, OrdersList* listOfOrders);
        // Constructor that also takes in player strategy
        Player(string* name, vector<Territory*> tCollection, Hand* hand, OrdersList* listOfOrders, PlayerStrategy* playerStrategy);
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
        void removeTerritory(string territoryName);
        void addTerritory(Territory* t);
        //assignment operator
        Player& operator =(const Player& e);
        //stream insertion operator
        friend ostream& operator<<(ostream& out, const Player& player);
        //getters
        string* getName();
        Hand* getHand();
        OrdersList* getOrdersList();
        vector<Territory*>* getTerritoryCollection();
        PlayerStrategy* getStrategy();
        int* getReinforcement();
        vector<Player*>* getNegotiating();
        bool* getHasConquered();
        bool* getWasAttacked();
        vector<Player*>* getPlayers();
        //setters
        void setTerritoriesToAttack();
        void setTerritoriesToDefend();
  
        bool hasCardInHand(string cardName);

        void setTerritoryCollection(vector <Territory*>*);
        void setReinforcement(int* number);
        void setName(string name);
        void setNegotiating(vector<Player*>* list);
        void setHasConquered(bool* check);
        void setStrategy(PlayerStrategy*);
        void setWasAttacked();
        void setPlayers(vector<Player*>* players);

};