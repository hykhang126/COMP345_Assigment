#include <list>
#include <string>
#include <vector>
#include "LoggingObserver.h"

using namespace std;

class State;

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

};



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
};



class GameEngine: public Subject, public ILoggable
{
    private :
        // // Command string
        // string *command;
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

        void initialization();

    public :
        State *getCurrentState();
        void setCurrentState(State *currentState);

        vector<State*> getStateList();
        void addStateToList(State* state);

        GameEngine();

        bool isCommandValid(string *command);

        string stringToLog();
    
};






