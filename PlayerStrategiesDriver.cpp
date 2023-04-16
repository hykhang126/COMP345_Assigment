#include <iostream>
#include <vector>
#include "Player.h"

//
// Created by Eric on 4/15/2023.
//
int main() {


    // ***********************
    // BENEVOLENT PLAYER
    // ***********************
    cout << "*****************\nBENEVOLENT STARTING HERE\n\"*****************\n";
    OrdersList* listOfOrders1 = new OrdersList();
    //creating players
    string* name1 = new string("Player1");

    // Create two continents
    Continent* continent1 = new Continent(new int(2), new string("Continent 1"), new int(10), new string("green"));

    // Create three territories
    Territory* territory1 = new Territory(new Player(), new int(3), new int(1), new string("Territory1"), continent1, new Coordinate(new int(1), new int(0)));
    Territory* territory2 = new Territory(new Player(), new int(7), new int(2), new string("Territory2"), continent1, new Coordinate(new int(2), new int(0)));
    Territory* territory3 = new Territory(new Player(), new int(4), new int(3), new string("Territory3"), continent1, new Coordinate(new int(3), new int(0)));
    Territory* territory4 = new Territory(new Player(), new int(4), new int(3), new string("Territory4"), continent1, new Coordinate(new int(4), new int(0)));


    Card* p1_card1 = new Card("bomb");
    Card* p1_card2 = new Card("airlift");
    //creating hands
    vector<Card*> player1Cards = {p1_card1, p1_card2};
    Hand* p1_hand = new Hand();
    p1_hand->setCardsInHand(player1Cards);

    vector<Territory*> tCollection1 = {territory1, territory2, territory3};

    auto collecter1Pter = new vector<Territory*>;
    collecter1Pter = &tCollection1;

    Player* player1 = new Player(name1, collecter1Pter, p1_hand, listOfOrders1);

    territory1->setOwner(player1);
    territory2->setOwner(player1);
    territory3->setOwner(player1);
    player1->setTerritoryCollection(collecter1Pter);
    vector<Territory*>* adjacent1 = new vector<Territory*>{territory1, territory2};
    vector<Territory*>* adjacent2 = new vector<Territory*>{territory2, territory4};

    territory1->setAdjacentTerritory(adjacent1);
    territory2->setAdjacentTerritory(adjacent1);
    territory4->setAdjacentTerritory(adjacent2);
    territory2->setAdjacentTerritory(adjacent2);
    // CREATING MAP
    // Add territories to the map
    Map* map1 = new Map();
    map1->addTerritory(territory1);
    map1->addTerritory(territory2);
    map1->addTerritory(territory4);
    // Add edges between territories
    map1->addEdge(territory1, territory2);
    map1->addEdge(territory2, territory1);
    map1->addEdge(territory2, territory4);
    map1->addEdge(territory4, territory2);
    vector<Continent*>* continents1 = new vector<Continent*>();
    continents1->push_back(continent1);
    map1->setContinentList(continents1);


    cout << "EXECUTION PHASE WOULD START HERE\n" << endl;

    vector<Player*> *players1 = new vector<Player*>;

    players1->push_back(player1);
    Deck *deck1 = new Deck(50);

    player1->setStrategy(new Benevolent(player1));

    player1->setReinforcement(new int(5));
    player1->issueOrder(players1, deck1);
    for (int i = 0; i < listOfOrders1->getList().size(); i++){
        listOfOrders1->getList().at(i)->execute();
    }


    // ***********************
    // AGGRESSIVE PLAYER
    // ***********************
    cout << "*****************\nAGGRESSIVE STARTING HERE\n\"*****************\n";
    OrdersList* listOfOrders2 = new OrdersList();
    //creating players
    string* name2 = new string("Player2");

    // Create two continents
    Continent* continent2 = new Continent(new int(2), new string("Continent 2"), new int(10), new string("red"));

    // Create three territories
    Territory* territory5 = new Territory(new Player(), new int(3), new int(1), new string("Territory5"), continent2, new Coordinate(new int(1), new int(0)));
    Territory* territory6 = new Territory(new Player(), new int(7), new int(2), new string("Territory6"), continent2, new Coordinate(new int(2), new int(0)));
    Territory* territory7 = new Territory(new Player(), new int(4), new int(3), new string("Territory7"), continent2, new Coordinate(new int(3), new int(0)));
    Territory* territory8 = new Territory(new Player(), new int(4), new int(3), new string("Territory8"), continent2, new Coordinate(new int(4), new int(0)));


    Card* p2_card1 = new Card("bomb");
    Card* p2_card2 = new Card("airlift");
    //creating hands
    vector<Card*> player2Cards = {p2_card1, p2_card2};
    Hand* p2_hand = new Hand();
    p2_hand->setCardsInHand(player2Cards);

    vector<Territory*> tCollection2 = {territory5, territory6, territory7};

    auto collecter2Pter = new vector<Territory*>;
    collecter2Pter = &tCollection2;

    Player* player2 = new Player(name2, collecter2Pter, p2_hand, listOfOrders2);

    territory5->setOwner(player2);
    territory6->setOwner(player2);
    territory7->setOwner(player2);
    player2->setTerritoryCollection(collecter2Pter);
    vector<Territory*>* adjacent3 = new vector<Territory*>{territory5, territory6};
    vector<Territory*>* adjacent4 = new vector<Territory*>{territory6, territory8};

    territory5->setAdjacentTerritory(adjacent3);
    territory6->setAdjacentTerritory(adjacent3);
    territory8->setAdjacentTerritory(adjacent4);
    territory6->setAdjacentTerritory(adjacent4);
    // CREATING MAP
    // Add territories to the map
    Map* map2 = new Map();
    map2->addTerritory(territory5);
    map2->addTerritory(territory6);
    map2->addTerritory(territory8);
    // Add edges between territories
    map2->addEdge(territory5, territory6);
    map2->addEdge(territory6, territory5);
    map2->addEdge(territory6, territory8);
    map2->addEdge(territory8, territory6);
    vector<Continent*>* continents2 = new vector<Continent*>();
    continents2->push_back(continent2);
    map2->setContinentList(continents2);


    cout << "EXECUTION PHASE WOULD START HERE\n" << endl;

    vector<Player*> *players2 = new vector<Player*>;

    players2->push_back(player2);
    Deck *deck2 = new Deck(50);

    player2->setStrategy(new Aggressive(player2));
    player2->setReinforcement(new int(5));
    player2->issueOrder(players2, deck2);
   listOfOrders2->getList().front()->execute();
   listOfOrders2->getList().at(1)->execute();
    listOfOrders2->getList().back()->execute();
    
    //Testing Human methods
    // player2->setStrategy(new Human(player2));
    // player2->toAttack();
    // player2->toDefend();
}