#ifndef GAMEENG_H
#define GAMEENG_H
#include <list>
#include <string>
#include <vector>

#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "CommandProcessor.h"

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
class GameEngine
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

        // CommandProcessor reference, where all commands are stored
        CommandProcessor *commandProcessor;

        void initialization();

    public :
        State *getCurrentState();
        void setCurrentState(State *currentState);

        vector<State*> getStateList();
        void addStateToList(State* state);

        vector<Player*>* getGamePlayers();
        void addPlayerToList(Player* player);

        GameEngine();
        GameEngine(CommandProcessor *commandProcessor);
        ~GameEngine();

        bool isCommandValid(string *command);

        string stringToLog();

        void startupPhase();
        void startupPhase(CommandProcessor* commandProcessor);
};

# endif