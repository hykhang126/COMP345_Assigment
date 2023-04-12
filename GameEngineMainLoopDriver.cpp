#include "GameEngine.cpp"

// MAIN
int main(int argc, char const *argv[])
{
    Deck* deck = new Deck(20);
    CommandProcessor *commandProcessor = new CommandProcessor();
    //CREATING PLAYERS
    Card* p1_card1 = new Card("bomb");
    Card* p1_card2 = new Card("airlift");
    //creating hands
    vector<Card*> playerCards = {p1_card1, p1_card2};
    Hand* p1_hand = new Hand();
    p1_hand->setCardsInHand(playerCards);
    Hand* p2_hand = new Hand();
    Hand* p3_hand = new Hand();
    //creating orders lists
    OrdersList* listOfOrders1 = new OrdersList();
    OrdersList* listOfOrders2 = new OrdersList();
    OrdersList* listOfOrders3 = new OrdersList();
    //creating players
    string* name1 = new string("Player1");
    string* name2 = new string("Player2");
    string* name3 = new string("Player3");

    // Create two continents
    Continent* continent1 = new Continent(new int(1), new string("Continent 1"), new int(5), new string("blue"));
    Continent* continent2 = new Continent(new int(2), new string("Continent 2"), new int(10), new string("red"));

    // Create three territories
    Territory* territory1 = new Territory(new Player(), new int(5), new int(0), new string("Territory1"), continent1, new Coordinate(new int(0), new int(0)));
    Territory* territory2 = new Territory(new Player(), new int(3), new int(1), new string("Territory2"), continent2, new Coordinate(new int(1), new int(0)));
    Territory* territory3 = new Territory(new Player(), new int(7), new int(2), new string("Territory3"), continent2, new Coordinate(new int(2), new int(0)));
    Territory* territory4 = new Territory(new Player(), new int(4), new int(3), new string("Territory4"), continent2, new Coordinate(new int(3), new int(0)));

    vector<Territory*> tCollection1 = {territory1};
    vector<Territory*> tCollection2 = {territory2};
    vector<Territory*> tCollection3 = {territory3, territory4, territory4, territory4, territory4, territory4, territory4, territory4, territory4, territory4, territory4, territory4,territory4};


    Player* player1 = new Player(name1, tCollection1, p1_hand, listOfOrders1);
    Player* player2 = new Player(name2, tCollection2, p2_hand, listOfOrders2);
    Player* player3 = new Player(name3, tCollection3, p3_hand, listOfOrders3);

    territory1->setOwner(player1);
    territory2->setOwner(player2);
    territory3->setOwner(player3);

    vector<Territory*>* adjacent1 = new vector<Territory*>{territory2, territory3};
    vector<Territory*>* adjacent2 = new vector<Territory*>{territory1, territory3};
    vector<Territory*>* adjacent3 = new vector<Territory*>{territory1, territory2};

    territory1->setAdjacentTerritory(adjacent1);
    territory2->setAdjacentTerritory(adjacent2);
    territory3->setAdjacentTerritory(adjacent3);
    //CREATING MAP
    // Add territories to the map
    Map* map = new Map();
    map->addTerritory(territory1);
    map->addTerritory(territory2);
    map->addTerritory(territory3);

    // Add edges between territories
    map->addEdge(territory1, territory2);
    map->addEdge(territory2, territory1);
    map->addEdge(territory2, territory3);
    map->addEdge(territory3, territory2);

    // Add continents to the map
    vector<Continent*>* continents = new vector<Continent*>();
    continents->push_back(continent1);
    continents->push_back(continent2);
    map->setContinentList(continents);

    //CREATE GAME ENGINE
    GameEngine *test = new GameEngine(commandProcessor, deck, map);
    
    //ADD PLAYERS TO GAME ENGINE
    test->addPlayerToList(player1);
    test->addPlayerToList(player2);
    test->addPlayerToList(player3);

    //SHOWING REINFORCEMENT PHASE
    test->reinforcementPhase();

    //SHOWING ISSUE ORDER PHASE
    test->issueOrdersPhase();
    
    cout << "EXECUTION PHASE WOULD START HERE\n" << endl;

    //SHOWING THAT MAIN GAME LOOP REMOVES PLAYERS WITH NO TERRITORIES AND HAS A PLAYER WIN IF OWN ALL TERRITORIES
    GameEngine *testWinner = new GameEngine(commandProcessor, deck, map);

    territory1->setOwner(player3);
    territory2->setOwner(player3);
    territory3->setOwner(player3);

    tCollection1 = {};
    tCollection2 = {};
    tCollection3 = {territory1, territory2, territory3};


    player1 = new Player(name1, tCollection1, p1_hand, listOfOrders1);
    player2 = new Player(name2, tCollection2, p2_hand, listOfOrders2);
    player3 = new Player(name3, tCollection3, p3_hand, listOfOrders3);
    testWinner->addPlayerToList(player1);
    testWinner->addPlayerToList(player2);
    testWinner->addPlayerToList(player3);
    testWinner->mainGameLoop();

    delete test;
    delete testWinner;
    return 0;
}
