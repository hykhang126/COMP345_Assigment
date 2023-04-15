#include <iostream>
#include <vector>
#include "Player.h"

//
// Created by Eric on 4/15/2023.
//
int main() {
    OrdersList* listOfOrders1 = new OrdersList();
    OrdersList* listOfOrders2 = new OrdersList();
    //creating players
    string* name1 = new string("Player1");
    string* name2 = new string("Player2");

    // Create two continents
    Continent* continent2 = new Continent(new int(2), new string("Continent 2"), new int(10), new string("red"));

    // Create three territories
    Territory* territory2 = new Territory(new Player(), new int(3), new int(1), new string("Territory2"), continent2, new Coordinate(new int(1), new int(0)));
    Territory* territory3 = new Territory(new Player(), new int(7), new int(2), new string("Territory3"), continent2, new Coordinate(new int(2), new int(0)));
    Territory* territory4 = new Territory(new Player(), new int(4), new int(3), new string("Territory4"), continent2, new Coordinate(new int(3), new int(0)));
    Territory* territory5 = new Territory(new Player(), new int(4), new int(3), new string("Territory5"), continent2, new Coordinate(new int(4), new int(0)));



    Card* p1_card1 = new Card("bomb");
    Card* p1_card2 = new Card("airlift");
    //creating hands
    vector<Card*> playerCards = {p1_card1, p1_card2};
    Hand* p1_hand = new Hand();
    p1_hand->setCardsInHand(playerCards);
    Hand* p2_hand = new Hand();
    Hand* p3_hand = new Hand();

    vector<Territory*> tCollection2 = {territory2, territory3, territory4};

    auto collecter2Pter = new vector<Territory*>;
    collecter2Pter = &tCollection2;

    Player* player2 = new Player(name2, collecter2Pter, p1_hand, listOfOrders2);

    territory2->setOwner(player2);
    territory3->setOwner(player2);
    territory4->setOwner(player2);
    player2->setTerritoryCollection(collecter2Pter);
    vector<Territory*>* adjacent1 = new vector<Territory*>{territory2, territory3};
    vector<Territory*>* adjacent2 = new vector<Territory*>{territory3, territory5};
//    vector<Territory*>* adjacent2 = new vector<Territory*>{territory1, territory3};
//    vector<Territory*>* adjacent3 = new vector<Territory*>{territory1, territory2};

//    territory1->setAdjacentTerritory(adjacent1);
    territory2->setAdjacentTerritory(adjacent1);
    territory3->setAdjacentTerritory(adjacent1);
    territory5->setAdjacentTerritory(adjacent2);
    territory3->setAdjacentTerritory(adjacent2);
    //CREATING MAP
    // Add territories to the map
    Map* map = new Map();
    map->addTerritory(territory2);
    map->addTerritory(territory3);
    map->addTerritory(territory5);
//    // Add edges between territories
//    map->addEdge(territory1, territory2);
//    map->addEdge(territory2, territory1);
    map->addEdge(territory2, territory3);
    map->addEdge(territory3, territory2);
    map->addEdge(territory3, territory5);
    map->addEdge(territory5, territory3);
    // Add continents to the map
    vector<Continent*>* continents = new vector<Continent*>();
//    continents->push_back(continent1);
    continents->push_back(continent2);
    map->setContinentList(continents);

    //CREATE GAME ENGINE

//    GameEngine *test = new GameEngine(commandProcessor, deck, map);

    //ADD PLAYERS TO GAME ENGINE
//    test->addPlayerToList(player1);
//    test->addPlayerToList(player2);
//    test->addPlayerToList(player3);
//
//    //SHOWING REINFORCEMENT PHASE
//    test->reinforcementPhase();

    //SHOWING ISSUE ORDER PHASE
//    test->issueOrdersPhase();

    cout << "EXECUTION PHASE WOULD START HERE\n" << endl;

    vector<Player*> *players = new vector<Player*>;

    players->push_back(player2);
    Deck *deck = new Deck(50);

    player2->setStrategy(new Aggressive(player2));

    player2->setReinforcement(new int(5));
    player2->issueOrder(players, deck);
   listOfOrders2->getList().front()->execute();
    listOfOrders2->getList().back()->execute();
    //SHOWING THAT MAIN GAME LOOP REMOVES PLAYERS WITH NO TERRITORIES AND HAS A PLAYER WIN IF OWN ALL TERRITORIES
//    GameEngine *testWinner = new GameEngine(commandProcessor, deck, map);
//
//    territory1->setOwner(player3);
//    territory2->setOwner(player3);
//    territory3->setOwner(player3);
//
//    tCollection1 = {};
//    tCollection2 = {};
//    tCollection3 = {territory1, territory2, territory3};
//
//
//    player1 = new Player(name1, tCollection1, p1_hand, listOfOrders1);
//    player2 = new Player(name2, tCollection2, p2_hand, listOfOrders2);
//    player3 = new Player(name3, tCollection3, p3_hand, listOfOrders3);
//    testWinner->addPlayerToList(player1);
//    testWinner->addPlayerToList(player2);
//    testWinner->addPlayerToList(player3);
//    testWinner->mainGameLoop();

}