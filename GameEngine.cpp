#include "GameEngine.h"

#include "CommandProcessor.cpp"
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

}

GameEngine::GameEngine()
{
    this->initialization();
}

GameEngine::GameEngine(CommandProcessor *commandProcessor)
{
    this->initialization();
    gamePlayers = new vector<Player*>;
    this->commandProcessor = commandProcessor;
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

void GameEngine::startupPhase(CommandProcessor* commandProcessor)
{
    /* Test command */
    currentState = validMapState;

    string choice = "NULL";
    Map* map;
    MapLoader mapLoader;
    Deck* deck = new Deck(20);
    int playerCount = gamePlayers->size();
    
    while (true)
    {
        cout << "  ***  Please input commands  ***  "<< endl;
        cout << "---------Enter 'stop' to stop giving commands. Enter any keys to continue---------" << endl;
        cin >> choice;
        if (choice.compare("stop") == 0) break;
        commandProcessor->GetCommand(currentState->getName());
        
    }
    
    cout << "  ***  Executing commands  ***  "<< endl;
    vector<Command*> *commandList = commandProcessor->ReturnCommandList();

    for (Command *command : *commandList)
    {
        choice = *command->getCommandName();

        if (choice.compare("loadmap") == 0)
        {
            string mapName = "france.txt";
            if (map == NULL)
            {
                map = mapLoader.loadMapFromFile(mapName);
                map->toString();
            }
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
            string *name = new string("Player ");
            name->append(std::to_string(playerCount));
            Hand *hand = new Hand();
            vector<Territory*> *tCollection = new vector<Territory*> {};
            OrdersList *listOfOrders = new OrdersList();

            Player* player = new Player(name, *tCollection, hand, listOfOrders);
            addPlayerToList(player);
            cout << *player->getName() << " added succesfully to player list" << endl;
            // Update State
            currentState = playersAddedState;
        }
        else if (choice.compare("gamestart") == 0)
        {
            // b) determine randomly the order of play of the players in the game
            std::random_device randomDevice;
            auto randomEngine = std::default_random_engine {randomDevice()};
            std::shuffle(gamePlayers->begin(), gamePlayers->end(), randomEngine);

            for (Player *player : *gamePlayers)
            {
                cout << *player->getName() << endl;
                // a) fairly distribute all the territories to the players  

                // c) give 50 initial armies to the players, which are placed in their respective reinforcement pool

                // d) let each player draw 2 initial cards from the deck using the deck’s draw() method
                //     // 1st card
                // deck->draw(player->getHand());
                //     // 2nd card
                // deck->draw(player->getHand());
            }
            // e) switch the game to the play phase
            currentState = assignReinState;
        }
    }

}

