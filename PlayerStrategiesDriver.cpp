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
    player1->issueOrder();
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
    player2->issueOrder();
    listOfOrders2->getList().front()->execute();
    listOfOrders2->getList().at(1)->execute();
    listOfOrders2->getList().back()->execute();
    

    // ***********************
    // NEUTRAL PLAYER
    // ***********************
    cout << "*****************\nNEUTRAL STARTING HERE\n\"*****************\n";
    OrdersList* listOfOrders3 = new OrdersList();
    //creating players
    string* name3 = new string("Player3");

    // Create two continents
    Continent* continent3 = new Continent(new int(2), new string("Continent 3"), new int(10), new string("blue"));

    // Create three territories
    Territory* territory9 = new Territory(new Player(), new int(3), new int(1), new string("Territory9"), continent3, new Coordinate(new int(1), new int(0)));
    Territory* territory10 = new Territory(new Player(), new int(7), new int(2), new string("Territory10"), continent3, new Coordinate(new int(2), new int(0)));
    Territory* territory11 = new Territory(new Player(), new int(4), new int(3), new string("Territory11"), continent3, new Coordinate(new int(3), new int(0)));
    Territory* territory12 = new Territory(new Player(), new int(4), new int(3), new string("Territory12"), continent3, new Coordinate(new int(4), new int(0)));


    Card* p3_card1 = new Card("bomb");
    Card* p3_card2 = new Card("airlift");
    //creating hands
    vector<Card*> player3Cards = {p3_card1, p3_card2};
    Hand* p3_hand = new Hand();
    p3_hand->setCardsInHand(player3Cards);

    vector<Territory*> tCollection3 = {territory9, territory10, territory11};

    auto collecter3Pter = new vector<Territory*>;
    collecter3Pter = &tCollection3;

    Player* player3 = new Player(name3, collecter3Pter, p3_hand, listOfOrders3);

    territory9->setOwner(player3);
    territory10->setOwner(player3);
    territory11->setOwner(player3);
    player3->setTerritoryCollection(collecter3Pter);
    vector<Territory*>* adjacent5 = new vector<Territory*>{territory9, territory10};
    vector<Territory*>* adjacent6 = new vector<Territory*>{territory10, territory12};

    territory9->setAdjacentTerritory(adjacent5);
    territory10->setAdjacentTerritory(adjacent5);
    territory12->setAdjacentTerritory(adjacent6);
    territory10->setAdjacentTerritory(adjacent6);
    // CREATING MAP
    // Add territories to the map
    Map* map3 = new Map();
    map3->addTerritory(territory9);
    map3->addTerritory(territory10);
    map3->addTerritory(territory12);
    // Add edges between territories
    map3->addEdge(territory9, territory10);
    map3->addEdge(territory10, territory9);
    map3->addEdge(territory10, territory12);
    map3->addEdge(territory12, territory10);
    vector<Continent*>* continents3 = new vector<Continent*>();
    continents3->push_back(continent3);
    map3->setContinentList(continents3);


    cout << "EXECUTION PHASE WOULD START HERE\n" << endl;

    vector<Player*> *players3 = new vector<Player*>;

    players3->push_back(player3);
    Deck *deck3 = new Deck(50);

    player3->setStrategy(new NeutralPlayerStrategy(player3));
    player3->setReinforcement(new int(5));
    player3->issueOrder();
    cout << "Player 3's list of orders after calling the issueOrder() method are the following: " << endl;
    cout << *listOfOrders3 << endl;
    
    //cout << "\nPlayer 3 is a player of type: " << *player3->getStrategy() << endl;
    cout << "\nPlayer 3 is a player of type: " << typeid(*player3->getStrategy()).name() << endl;
    player3->setWasAttacked();
    //when calling to attack on this player after setting his wasAttacked status to true, the player will become an aggressive player and call the to
    //attack method of the aggressive class
    player3->toAttack();
    //cout << "\nPlayer 3 is a player of type: " << *player3->getStrategy() << endl; 
    cout << "\nPlayer 3 is a player of type: " << typeid(*player3->getStrategy()).name() << endl;


    // ***********************
    // CHEATER PLAYER
    // ***********************
    cout << "*****************\nCHEATER STARTING HERE\n\"*****************\n";
    OrdersList* listOfOrders4 = new OrdersList();
    //creating players
    string* name4 = new string("Player4");

    // Create two continents
    Continent* continent4 = new Continent(new int(2), new string("Continent 4"), new int(10), new string("red"));

    // Create three territories
    Territory* territory13 = new Territory(new Player(), new int(3), new int(1), new string("Territory13"), continent4, new Coordinate(new int(1), new int(0)));
    Territory* territory14 = new Territory(new Player(), new int(7), new int(2), new string("Territory14"), continent4, new Coordinate(new int(2), new int(0)));
    Territory* territory15 = new Territory(new Player(), new int(4), new int(3), new string("Territory15"), continent4, new Coordinate(new int(3), new int(0)));
    Territory* territory16 = new Territory(new Player(), new int(4), new int(3), new string("Territory16"), continent4, new Coordinate(new int(4), new int(0)));

    Card* p4_card1 = new Card("bomb");
    Card* p4_card2 = new Card("airlift");
    //creating hands
    vector<Card*> player4Cards = {p4_card1, p4_card2};
    Hand* p4_hand = new Hand();
    p4_hand->setCardsInHand(player4Cards);

    vector<Territory*> tCollection4 = {territory13, territory14, territory15};
    
    auto collecter4Pter = new vector<Territory*>;
    collecter4Pter = &tCollection4;
    
    Player* player4 = new Player(name4, collecter4Pter, p4_hand, listOfOrders4);

    territory13->setOwner(player4);
    territory14->setOwner(player4);
    territory15->setOwner(player4);
    player4->setTerritoryCollection(collecter4Pter);
    vector<Territory*>* adjacent7 = new vector<Territory*>{territory13, territory14};
    vector<Territory*>* adjacent8 = new vector<Territory*>{territory14, territory16};

    territory13->setAdjacentTerritory(adjacent7);
    territory14->setAdjacentTerritory(adjacent7);
    territory16->setAdjacentTerritory(adjacent8);
    territory14->setAdjacentTerritory(adjacent8);
    // CREATING MAP
    // Add territories to the map
    Map* map4 = new Map();
    map4->addTerritory(territory13);
    map4->addTerritory(territory14);
    map4->addTerritory(territory16);
    // Add edges between territories
    map4->addEdge(territory13, territory14);
    map4->addEdge(territory14, territory13);
    map4->addEdge(territory14, territory16);
    map4->addEdge(territory16, territory14);
    vector<Continent*>* continents4 = new vector<Continent*>();
    continents4->push_back(continent4);
    map4->setContinentList(continents4);


    cout << "EXECUTION PHASE WOULD START HERE\n" << endl;

    vector<Player*> *players4 = new vector<Player*>;

    players4->push_back(player4);
    Deck *deck4 = new Deck(50);

    player4->setStrategy(new CheaterPlayerStrategy(player4));
    player4->setReinforcement(new int(5));
    vector<Territory*>* currentTers = player4->toDefend();
    cout << "\nThe following territories is a list of territories that player 4 currently owns: " << endl;
    for(auto ter : *currentTers) {
        cout << *ter->getName() << endl;
    }

    cout << "\nThe current owner of territory 16 is: " << *territory16->getOwner()->getName() << endl;

    player4->issueOrder();

    cout << "\nPlayer 4 now owns the following territories after calling issueOrder(): " << endl;
    currentTers = player4->toDefend();
    for(auto ter : *currentTers) {
        cout << *ter->getName() << endl;
    }

    cout << "\nThe owner of territory 16 is: " << *territory16->getOwner()->getName() << endl;



    //**********************************
    //HUMAN METHODS
    //**********************************
    cout << "*****************\nHUMAN STARTING HERE\n\"*****************\n";
    OrdersList* listOfOrders5 = new OrdersList();
    //creating players
    string* name5 = new string("Player5");

    // Create two continents
    Continent* continent5 = new Continent(new int(2), new string("Continent 5"), new int(10), new string("black"));

    // Create three territories
    Territory* territory17 = new Territory(new Player(), new int(3), new int(1), new string("Territory17"), continent5, new Coordinate(new int(1), new int(0)));
    Territory* territory18 = new Territory(new Player(), new int(7), new int(2), new string("Territory18"), continent5, new Coordinate(new int(2), new int(0)));
    Territory* territory19 = new Territory(new Player(), new int(4), new int(3), new string("Territory19"), continent5, new Coordinate(new int(3), new int(0)));
    Territory* territory20 = new Territory(new Player(), new int(4), new int(3), new string("Territory20"), continent5, new Coordinate(new int(4), new int(0)));

    Card* p5_card1 = new Card("bomb");
    Card* p5_card2 = new Card("airlift");
    //creating hands
    vector<Card*> player5Cards = {p5_card1, p5_card2};
    Hand* p5_hand = new Hand();
    p5_hand->setCardsInHand(player5Cards);

    vector<Territory*> tCollection5 = {territory17, territory18, territory19};
    
    auto collecter5Pter = new vector<Territory*>;
    collecter5Pter = &tCollection5;
    
    Player* player5 = new Player(name5, collecter5Pter, p5_hand, listOfOrders5);

    territory17->setOwner(player5);
    territory18->setOwner(player5);
    territory19->setOwner(player5);
    player5->setTerritoryCollection(collecter5Pter);
    vector<Territory*>* adjacent9 = new vector<Territory*>{territory17, territory18};
    vector<Territory*>* adjacent10 = new vector<Territory*>{territory18, territory20};

    territory17->setAdjacentTerritory(adjacent9);
    territory18->setAdjacentTerritory(adjacent9);
    territory19->setAdjacentTerritory(adjacent10);
    territory20->setAdjacentTerritory(adjacent10);
    // CREATING MAP
    // Add territories to the map
    Map* map5 = new Map();
    map5->addTerritory(territory17);
    map5->addTerritory(territory18);
    map5->addTerritory(territory20);
    // Add edges between territories
    map5->addEdge(territory17, territory18);
    map5->addEdge(territory18, territory17);
    map5->addEdge(territory18, territory20);
    map5->addEdge(territory20, territory18);
    vector<Continent*>* continents5 = new vector<Continent*>();
    continents5->push_back(continent5);
    map5->setContinentList(continents5);


    cout << "EXECUTION PHASE WOULD START HERE\n" << endl;

    vector<Player*> *players5 = new vector<Player*>;

    players5->push_back(player5);
    Deck *deck5 = new Deck(50);

    player5->setStrategy(new Human(player5));
    player5->setReinforcement(new int(5));
    player5->issueOrder();

    for(Order* order : player5->getOrdersList()->getList()) {
        order->execute();
    }
}