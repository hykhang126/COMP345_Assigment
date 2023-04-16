#include "GameEngine.h"

#include "CommandProcessing.cpp"
#include "Player.cpp"
#include "Cards.cpp"
#include "Orders.cpp"
#include "LoggingObserver.cpp"
#include "Map.cpp"



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
int GameEngine::M;
int GameEngine::P;
int GameEngine::G;
int GameEngine::D;

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
    startTran = new Transition(new string("loadMap"), loadState);
    loadTran_1 = startTran;
    loadTran_2 = new Transition(new string("validateMap"), validMapState);
    validMapTran = new Transition(new string("addPlayer"), playersAddedState);
    playersAddedTran_1 = validMapTran;
    playersAddedTran_2 = new Transition(new string("assigncountries"), assignReinState);
    assignReinTran = new Transition(new string("issueorder"), issueOrderState);
    issueOrderTran_1 = assignReinTran;
    issueOrderTran_2 = new Transition(new string("endissueorders"), executeOrderState);
    executeOrderTran_1 = new Transition(new string("execorder"), executeOrderState);
    executeOrderTran_2 = new Transition(new string("endexecorders"), assignReinState);
    executeOrderTran_3 = new Transition(new string("win"), winState);
    winTran_1 = new Transition(new string("play"), startState);
    winTran_2 = new Transition(new string("end"), NULL);

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

    MapLoader loader;
    nameOfMapVector = new vector<string>();
    nameOfMapVector->push_back("haiti.txt");
    nameOfMapVector->push_back("brasil.txt");
    nameOfMapVector->push_back("eire.txt");
    nameOfMapVector->push_back("germany.txt");
    nameOfMapVector->push_back("france.txt");

    GameEngine::D = 0;
}

string* GameEngine::currentStateToString()
{
    State* st = this->getCurrentState();
    return st->getName();
}

GameEngine::GameEngine()
{
    this->initialization();
    CommandProcessor *commandProcessor = new CommandProcessor();
    commandProcessor->GetCommand(this->currentStateToString());
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
    delete startTran, loadTran_1, loadTran_2, validMapTran, playersAddedTran_1, playersAddedTran_2, assignReinTran, issueOrderTran_1,
        issueOrderTran_2, executeOrderTran_1, executeOrderTran_2, executeOrderTran_3, winTran_1, winTran_2;
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
            notify(this);
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
    for(int i = 1; i<map->countTerritory(); i++) {
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
    for(Player* player: *gamePlayers)
    {
        cout << *player->getName() << " will now issue orders\n" << endl;
        player->issueOrder();
    }
}

void GameEngine::executeOrdersPhase() {
    cout << "EXECUTE ORDERS PHASE\n" << endl;
    for(Player* player: *gamePlayers){
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
    cout << "MAIN GAME LOOP" << endl;
    Player* winner = nullptr;
    do{
        //Remove players who do not own any territories
        for (int i = 0; i < gamePlayers->size(); i++) {
            if ((*gamePlayers)[i]->getTerritoryCollection()->empty()) {
                cout << "Player " << *((*gamePlayers)[i]->getName()) << " has been eliminated from the game as he does not own any territories.\n";
                delete (*gamePlayers)[i];
                gamePlayers->erase(gamePlayers->begin() + i);
                i--;
            }
        }       

        //Declare winner if a player owns all territories
        for(Player* player : *gamePlayers){
            if(map->countTerritory() == player->getTerritoryCollection()->size()){
                cout << "Player " << *(player->getName()) << " owns all territories on the map. They win the game!\n";
                winner = player;
                break;
            }
        }

        if(winner != nullptr) {
            break;
        }

        cout << "Starting reinforcement phase" << endl;
        this->reinforcementPhase();
        cout << "Starting issue orders phase" << endl;
        this->issueOrdersPhase();
        cout << "Starting execute orders phase" << endl;
        this->executeOrdersPhase();

    } while(true);
   
   return *winner;
}

void GameEngine::distributeTerritory(Player* player)
{
    int maxNumTerritories = map->countTerritory();
    int maxNumTerritoriesPerPlayer = 5;
    vector<Territory*>* tCollection = new vector<Territory*>();
    Territory* territory;
    int countTerritories = 0;

    while (countTerritories < maxNumTerritoriesPerPlayer)
    {
        int randomIndex = rand() % (maxNumTerritories-1) + 1;
        if (map != nullptr && map->getTerritoryByIndex(randomIndex) != nullptr) 
            territory = map->getTerritoryByIndex(randomIndex);
        else 
        {
            cout << " Territory* is null" << endl;
            break;
        }


        if (territory->getOwner() == nullptr)
        {
            tCollection->push_back(territory);
            territory->setOwner(player);
            countTerritories++;
        }
    }
    
    player->setTerritoryCollection(tCollection);
    for (Territory *ter : *player->getTerritoryCollection())
    {
        if (ter != nullptr) cout << ter->toString() << endl;
        else cout << "ter is null" << endl;
    }
}

void GameEngine::startupPhase()
{
    // ADD MAP
    MapLoader mapLoader;
    string mapName = "france.txt";
    map = mapLoader.loadMapFromFile(mapName);
    map->toString();
    // Update State
    currentState = loadState;

    // VALIDATE MAP
    map->validate();
    // Update State
    currentState = validMapState;

    // ADD PLAYER
    for (int i = 0; i < GameEngine::P; i++)
    {
        string playerName = "Player";
        playerName.append(std::to_string(i));

        Player* player = new Player();
        player->setName(playerName);

        // a) fairly distribute all the territories to the players  
        distributeTerritory(player);

        addPlayerToList(player);
        cout << *player->getName() << " added succesfully to player list" << endl;
        cout << "---------------------" << endl;
    }
    // Update State
    currentState = playersAddedState;

    // START GAME
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

Player* GameEngine::GameUpdate()
{
    currentState = startState;
    startupPhase();
    Player* winner;
    *winner = mainGameLoop();
    return winner;
}

void GameEngine::OutputResult(Player *winner, int i, int j)
{
    cout << *winner->getName() << endl;
    ofstream logFile;
    logFile.open (".\\gameResultLog.txt", ios::app);
    if (winner != nullptr)
        logFile << "Map: " << i << ", Game: " << j << ", Winner: " << *winner->getName() << endl;
    else
        logFile << "Map: " << i << ", Game: " << j << ", Winner: DRAW!" << endl;
    
    logFile.close();
}

void GameEngine::Tournament()
{
    commandProcessor->GetCommand(currentState->getName());

    ofstream logFile;
    logFile.open (".\\gameResultLog.txt", ios::app);
    logFile << "Tournament mode:" << endl << "M: ";
    //output list a map names
    for (int i = 0; i < GameEngine::M; i++)
    {
        logFile << "Map " << i << ". ";
    }
    
    // for (Map* map : *mapList)
    // {
    //     logFile << "A" << ", ";
    // }
    logFile << "\n";
    logFile << "P: " << GameEngine::P << endl;
    logFile << "G: " << GameEngine::G << endl;
    logFile << "D: " << GameEngine::D << endl;
    logFile << "Results: " << endl;
    logFile.close();

    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; i < 2; j++)
        {
            Player* winner = GameUpdate();
            OutputResult(winner, i, j);
        }
        
    }
    
}