#pragma once
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

#include "LoggingObserver.h"
#include "Map.h"
#include "Orders.h"
#include "Player.h"
#include "Cards.h"
#include "CommandProcessing.h"
#include "PlayerStrategies.h"


using namespace std;

class State;

// Transition class
class Transition
{
    private :
        string *name;
        State *destination;
    
    public:
        string *getName();
        void setName(string *name);

        State *getDestination();
        void setDestination(State *state);

        Transition();
        Transition(string *name, State *destination);
        ~Transition();

};



// State class
class State
{
    private :
        string *name;
        vector<Transition*> transitions;
    
    public:
        void addTransitionsToState(Transition *transition);
        void showTransitions();

        string *getName();
        void setName(string *name);

        vector<Transition*> getTransitions();
        void setTransitions(vector<Transition*> transitions);

        State();
        State(string *name);
        ~State();
};



// GameEngine class
class GameEngine: public Subject, public ILoggable
{
    private :
        // currentState to store current state of the game
        State* currentState;
        // All 8 States
        State* startState;
        State* loadState;
        State* validMapState;
        State* playersAddedState;
        State* assignReinState;
        State* issueOrderState;
        State* executeOrderState;
        State* winState;
        // List of all states except current state
        vector<State*> stateList;

        // All 14 transitions
        Transition *startTran;
        Transition *loadTran_1;
        Transition *loadTran_2;
        Transition *validMapTran;
        Transition *playersAddedTran_1;
        Transition *playersAddedTran_2;
        Transition *assignReinTran;
        Transition *issueOrderTran_1;
        Transition *issueOrderTran_2;
        Transition *executeOrderTran_1;
        Transition *executeOrderTran_2;
        Transition *executeOrderTran_3;
        Transition *winTran_1;
        Transition *winTran_2;


        // Player list
        vector<Player*>* gamePlayers;

        // CommandProcessor reference, where all commands are handled
        CommandProcessor *commandProcessor;

        // Deck reference, where all cards and deck are stored
        Deck *deck;

        // Map reference, where the map is stored
        Map *map;

        vector<Map*>* mapList;

        void initialization();
        

    public :
        static int M;
        static int D;
        static int G;
        static int P;
        vector<string>* nameOfMapVector;
        string* currentStateToString();
        State *getCurrentState();
        void setCurrentState(State *currentState);
        vector<Player*>& getPlayers();

        vector<State*> getStateList();
        void addStateToList(State* state);

        GameEngine();

        bool playerOwnsContinent(Player * player, Continent* continent, Map* map);

        string stringToLog() override;
        void reinforcementPhase();
        void issueOrdersPhase();
        void executeOrdersPhase();
        Player* mainGameLoop();

        vector<Player*>* getGamePlayers();
        void addPlayerToList(Player* player);


        Deck *getDeck();
        void setDeck(Deck *deck);

        Map *getMap();
        void setMap(Map *map);

        GameEngine(CommandProcessor *commandProcessor, Deck *deck,  Map *map);
        GameEngine(CommandProcessor *commandProcessor);
        ~GameEngine();

        bool isCommandValid(string *command);
        void distributeTerritory(Player* player);

        void startupPhase();

        Player* GameUpdate();
        void OutputResult(Player *winner, int i, int j);
        void RestartGameUpdate();
        void Tournament();
};