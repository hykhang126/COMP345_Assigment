#include "GameEngine.h"

#include "CommandProcessing.cpp"
#include "Player.cpp"
#include "Cards.cpp"
#include "Orders.cpp"
#include "LoggingObserver.cpp"
#include "Map.cpp"

#include <iostream>
#include <algorithm>



// STATE CLASS
State::State()
{
    this->name = NULL;
}

State::State(string *name)
{
    this->name = name;
}

State::~State()
{
    for (Transition* trans : transitions)
    {
        delete trans;
    }
    
}

void State::addTransitionsToState(Transition *transition)
{
    this->transitions.push_back(transition);
}

void State::showTransitions()
{
    cout << "State " << *this->getName() << ": ";
    for (int i = 0; i < this->transitions.size(); i++)
    {
        cout << *this->transitions[i]->getName() << ", ";
    }
    cout << endl;
    
}

string *State::getName()
{
    return name;
}

void State::setName(string *name)
{
    this->name = name;
}

vector<Transition*> State::getTransitions()
{
    return this->transitions;
}

void State::setTransitions(vector<Transition*> transitions)
{
    this->transitions = transitions;
}





// TRANSITION CLASS
Transition::Transition()
{
    this->name = new string("N/A");
    this->destination = NULL;

}

Transition::Transition(string *name, State *destination)
{
    this->name = name;
    this->destination = destination;
}

Transition::~Transition()
{
    delete name;
}

string *Transition::getName()
{
    return name;
}

void Transition::setName(string *name)
{
    this->name = name;
}

State *Transition::getDestination()
{
    return this->destination;
}

void Transition::setDestination(State *destination)
{
    this->destination = destination;
}





// GAME ENGINE CLASS
vector<State*> GameEngine::getStateList()
{
    return this->stateList;
}

void GameEngine::addStateToList(State* state)
{
    this->stateList.push_back(state);
}

State *GameEngine::getCurrentState()
{
    return GameEngine::currentState;
}

void GameEngine::setCurrentState(State *currentState)
{
    this->currentState = currentState;
}

vector<Player*>* GameEngine::getGamePlayers()
{
    return this->gamePlayers;
}

void GameEngine::addPlayerToList(Player* player)
{
    this->gamePlayers->push_back(player);
}


Deck * GameEngine::getDeck()
{
    return this->deck;
}

void  GameEngine::setDeck(Deck *deck)
{
    this->deck = deck;
}

Map * GameEngine::getMap()
{
    return this->map;
}

void  GameEngine::setMap(Map *map)
{
    this->map = map;
}

void GameEngine::initialization()
{
    // Create all states 
    startState = new State(new string("Start"));
    loadState = new State(new string("MapLoaded"));
    validMapState = new State(new string("MapValidated"));
    playersAddedState = new State(new string("PlayersAdded"));
    assignReinState = new State(new string("AssignReinforcement"));
    issueOrderState = new State(new string("IssueOrder"));
    executeOrderState = new State(new string("ExecuteOrder"));
    winState = new State(new string("Win"));

    // Create all transitions;
    Transition *startTran = new Transition(new string("loadMap"), loadState);
    Transition *loadTran_1 = startTran;
    Transition *loadTran_2 = new Transition(new string("validateMap"), validMapState);
    Transition *validMapTran = new Transition(new string("addPlayer"), playersAddedState);
    Transition *playersAddedTran_1 = validMapTran;
    Transition *playersAddedTran_2 = new Transition(new string("assigncountries"), assignReinState);
    Transition *assignReinTran = new Transition(new string("issueorder"), issueOrderState);
    Transition *issueOrderTran_1 = assignReinTran;
    Transition *issueOrderTran_2 = new Transition(new string("endissueorders"), executeOrderState);
    Transition *executeOrderTran_1 = new Transition(new string("execorder"), executeOrderState);
    Transition *executeOrderTran_2 = new Transition(new string("endexecorders"), assignReinState);
    Transition *executeOrderTran_3 = new Transition(new string("win"), winState);
    Transition *winTran_1 = new Transition(new string("play"), startState);
    Transition *winTran_2 = new Transition(new string("end"), NULL);

    // Add all 14 transitions to 8 states;
    startState->addTransitionsToState(startTran);
    loadState->addTransitionsToState(loadTran_1);
    loadState->addTransitionsToState(loadTran_2);
    validMapState->addTransitionsToState(validMapTran);
    playersAddedState->addTransitionsToState(playersAddedTran_1);
    playersAddedState->addTransitionsToState(playersAddedTran_2);
    assignReinState->addTransitionsToState(assignReinTran);
    issueOrderState->addTransitionsToState(issueOrderTran_1);
    issueOrderState->addTransitionsToState(issueOrderTran_2);
    executeOrderState->addTransitionsToState(executeOrderTran_1);
    executeOrderState->addTransitionsToState(executeOrderTran_2);
    executeOrderState->addTransitionsToState(executeOrderTran_3);
    winState->addTransitionsToState(winTran_1);
    winState->addTransitionsToState(winTran_2);

    // Add all 8 state to stateList
    this->addStateToList(startState);
    this->addStateToList(loadState);
    this->addStateToList(validMapState);
    this->addStateToList(playersAddedState);
    this->addStateToList(assignReinState);
    this->addStateToList(issueOrderState);
    this->addStateToList(executeOrderState);
    this->addStateToList(winState);

    this->setCurrentState(startState);

    delete startTran, loadTran_1, loadTran_2, validMapTran, playersAddedTran_1, playersAddedTran_2, assignReinTran, issueOrderTran_1, 
            issueOrderTran_2, executeOrderTran_1, executeOrderTran_2, executeOrderTran_3, winTran_1, winTran_2;
}

GameEngine::GameEngine()
{
    this->initialization();
}

GameEngine::GameEngine(CommandProcessor *commandProcessor, Deck *deck, Map *map)
{
    this->initialization();
    gamePlayers = new vector<Player*>;
    this->commandProcessor = commandProcessor;
    this->deck = deck;
    this->map = map;
}

GameEngine::~GameEngine()
{
    for (State* trans : stateList)
    {
        trans->~State();
        delete trans;
    }
    
    delete gamePlayers;
}

bool GameEngine::isCommandValid(string *command)
{
    cout << "-----------------------------\n";
    cout << "Current State and its transitions:\n - ";
    currentState->showTransitions();
    cout << "Your command: " << *command;
    cout << endl;

    vector<Transition*> currTransitions = currentState->getTransitions();
    for (int i = 0; i < currTransitions.size(); i++)
    {
        if (currTransitions[i]->getName()->compare(*command) == 0)
        {
            currentState = currTransitions[i]->getDestination();
            cout << "Command Valid. State changed\n" << endl;
            return true;
        }
    }
    cout << "Command Invalid\n" << endl;
    return false;
}

string GameEngine::stringToLog() 
{
    return "LOG: Game engine transitioning to state " + *currentState->getName();
}


vector<Player*>& GameEngine::getPlayers(){
    return *gamePlayers;
}

bool GameEngine::playerOwnsContinent(Player* player, Continent* continent, Map* map) {
    vector<Territory*> territoriesInContinent;
    for(int i = 0; i<map->countTerritory(); i++) {
        Territory* territory = map->getTerritoryByIndex(i);
        if (territory->getContinent() == continent){
            territoriesInContinent.push_back(territory);
        }
    }

    for(auto territory : territoriesInContinent) {
        if(territory->getOwner() != player){
            return false;
        }
    }
    return true;
}

void GameEngine::reinforcementPhase() {
    // # of territories / 3 to added to the army pool
    cout << "BEGINNING OF REINFORCEMENT PHASE\n" << endl;
    for(Player* player: this->getPlayers()){
        int* newReinforcementValue;
        int reinforcementValue = player->getTerritoryCollection()->size() / 3;
        cout << "Based on the number of territories " << *player->getName() <<" owns, your calculated reinforcement value is " << reinforcementValue << endl;
        if(reinforcementValue < 3) { //minimum of 3 army points per round
            cout << "Since that value is less than 3, you will have 3 armies added to your reinforcements this round" << endl;
            newReinforcementValue = new int(3 + *player->getReinforcement());
            player->setReinforcement(newReinforcementValue);
        } else { //if territories/3 is greater than 3, add that number to the reinforcement armies
            cout << *player->getName() <<" will have " << reinforcementValue << " armies added to they reinforcements" << endl;
            newReinforcementValue = new int(reinforcementValue + *player->getReinforcement());
            player->setReinforcement(newReinforcementValue);
        }
        cout << *player->getName() <<" now has " << *player->getReinforcement() << " reinforcement armies\n" << endl;
    }

    //Bonus Army
    for(Player* player: this->getPlayers()) {
        int* newReinforcementValue;
        for(Continent* c : *map->getContinentList()) {
            if(this->playerOwnsContinent(player, c, map)){
                cout << *player->getName() <<" owns all the territories on " << *c->getName() << ", they will be given a bonus of " << *c->getPoint() << endl;
                newReinforcementValue = new int(*c->getPoint() + *player->getReinforcement());
                player->setReinforcement(newReinforcementValue);
                cout << *player->getName() <<" now has " << *player->getReinforcement() << " reinforcement armies\n" << endl;
            }
        }
    }
}

void GameEngine::issueOrdersPhase() {
    cout << "ISSUE ORDERS PHASE\n" << endl; 
    for(Player* player: this->getPlayers()){
        cout << *player->getName() << " will now issue orders\n" << endl;
        player->issueOrder(gamePlayers, deck);
    }
}

void GameEngine::executeOrdersPhase() {
    cout << "EXECUTE ORDERS PHASE\n" << endl;
    for(Player* player: this->getPlayers()){
        OrdersList* orderList = player->getOrdersList();
        while(!orderList->getList().empty()) {
            //get first order of list
            Order* order = orderList->getList().front();
            //exectue order
            order->execute();
            //remove order
            orderList->remove(order);
        }
    }
}

Player GameEngine::mainGameLoop() {
    Player* winner = nullptr;
    do{
        cout << "Starting reinforcement phase" << endl;
        this->reinforcementPhase();
        cout << "Starting issue orders phase" << endl;
        this->issueOrdersPhase();
        cout << "Starting execute orders phase" << endl;
        this->executeOrdersPhase();

        //Remove players who do not own any territories
        vector<Player*>::iterator it = gamePlayers->begin();
        while(it != gamePlayers->end()) {
            if ((*it)->getTerritoryCollection()->empty()){
                cout << "Player " << *((*it)->getName()) << " has been eliminated from the game.\n";
                delete *it;
                it = gamePlayers->erase(it);
            } else {
                ++it;
            }
        }

        //Declare winner if a player owns all territories
        for(Player* player : *gamePlayers){
            if(map->countTerritory() == player->getTerritoryCollection()->size()){
                cout << "Player " << *(player->getName()) << " owns all territories on the map. They win the game!\n";
                winner = player;
            }
        }

    } while(winner == nullptr);
   
   return *winner;
}

void GameEngine::distributeTerritory(Player* player)
{
    int maxNumTerritories = map->countTerritory();
    int maxNumTerritoriesPerPlayer = 5;
    vector<Territory*> tCollection = {};
    Territory* territory;
    int countTerritories = 0;

    while (countTerritories < maxNumTerritoriesPerPlayer)
    {
        int randomIndex = rand() % (maxNumTerritories-1) + 1;
        cout << randomIndex << endl;
        if (map != nullptr && map->getTerritoryByIndex(randomIndex) != nullptr) 
            territory = map->getTerritoryByIndex(randomIndex);
        else 
        {
            cout << " Territory* is null" << endl;
            break;
        }


        if (territory->getOwner() == nullptr)
        {
            tCollection.push_back(territory);
            territory->setOwner(player);
            countTerritories++;
        }
    }
    
    player->setTerritoryCollection(&tCollection);
    for (Territory *ter : *player->getTerritoryCollection())
    {
        if (ter != nullptr) cout << ter->toString() << endl;
        else cout << "ter is null" << endl;
    }
}

void GameEngine::startupPhase()
{
    // /* Test command */
    // currentState = playersAddedState;

    string choice = "NULL";
    MapLoader mapLoader;
    int playerCount = gamePlayers->size();

    cout << "\n  ***  Please input commands  ***  "<< endl;
    commandProcessor->GetCommand(currentState->getName());
    
    cout << "\n  ***  Executing commands  ***  "<< endl;
    vector<Command*> *commandList = commandProcessor->ReturnCommandList();

    for (Command *command : *commandList)
    {
        choice = *command->getCommandName();
        string effect = command->getEffect();

        // Check if this command is already executed. If yes then skip it
        if (effect.compare("true") != 0) continue;

        if (choice.compare("loadmap") == 0)
        {
            string mapName = "france.txt";
            map = mapLoader.loadMapFromFile(mapName);
            map->toString();
            // Update State
            currentState = loadState;
        }
        else if (choice.compare("validatemap") == 0)
        {
            map->validate();
            // Update State
            currentState = validMapState;
        }
        else if (choice.compare("addplayer") == 0)
        {
            playerCount++;
            string playerName = "Player";
            playerName.append(std::to_string(playerCount));
            vector<Territory*> tCollection = {};
            Hand hand;
            OrdersList listOfOrders;

            Player* player = new Player(&playerName, tCollection, &hand, &listOfOrders);

            // a) fairly distribute all the territories to the players  
            distributeTerritory(player);

            addPlayerToList(player);
            cout << *player->getName() << " added succesfully to player list" << endl;
            cout << "---------------------" << endl;
            // Update State
            currentState = playersAddedState;

        }
        else if (choice.compare("gamestart") == 0)
        {
            // b) determine randomly the order of play of the players in the game
            std::random_device randomDevice;
            auto randomEngine = std::default_random_engine {randomDevice()};
            std::shuffle(gamePlayers->begin(), gamePlayers->end(), randomEngine);

              for (const auto& player : *gamePlayers)
            {
                cout << endl << "---" << *player->getName() << "---" << endl;

                // c) give 50 initial armies to the players, which are placed in their respective reinforcement pool
                player->setReinforcement(new int(50));
                cout << "Number of initial armies: " << *player->getReinforcement() << endl;
                cout << "---------------------" << endl;

                // d) let each player draw 2 initial cards from the deck using the deck’s draw() method
                    // 1st card
                deck->draw(player->getHand());
                    // 2nd card
                deck->draw(player->getHand());
                    // Find some way to show the 2 drawn cards
                cout << "Number of cards on hand: " << player->getHand()->getCardsInHand().size() << endl;
                cout << "---------------------" << endl;
            }
            // e) switch the game to the play phase
            currentState = assignReinState;
        }
        // Update the command effect to be already executed
        command->SaveEffect(new string("executed"));
        cout << "---------------------" << endl;
    }
}

