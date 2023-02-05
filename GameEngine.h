#include <list>
#include <string>


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
        Transition *transitions[];
    
    public:
        string *getName();
        void setName(string *name);

        Transition *getTransitions();
        void setTransitions(Transition *transitions[]);

        State();
        State(string *name);
        State(string *name, Transition *transitions[]);
};




class GameEngine
{
    private :
        State* currentState;

        

    public :
        State *getCurrentState();
        void setCurrentState(State *currentState);

        void toString();
        GameEngine();
    
};








class Command
{
    private :
        string *name;
    
    public:
        int isCommandValid(string *command);
};