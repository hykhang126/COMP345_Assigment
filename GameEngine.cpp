#include "GameEngine.h"
#include <iostream>





// STATE CLASS
State::State()
{

}

State::State(string *name)
{
    this->name = name;
}

string *State::getName()
{
    return name;
}

Transition *State::getTransitions()
{
    return this->transitions[0];
}

void State::setTransitions(Transition *transitions[])
{
    this->transitions[0] = transitions[0];
}





// TRANSITION CLASS
Transition::Transition()
{
    
}

Transition::Transition(string *name, State *destination)
{
    this->name = name;
    this->destination = destination;
}

string *Transition::getName()
{
    return name;
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
GameEngine::GameEngine()
{
    // Create all states with their transitions;
    string tempName = "Start";
    State *startState = new State(&tempName);
    tempName = "Map Loaded";
    State *loadState = new State(&tempName);
    tempName = "Map Validated";
    State *validMapState = new State(&tempName);
    tempName = "Players Added";
    State *addPlayerState = new State(&tempName);

    tempName = "loadmap";
    Transition *loadTran_1 = new Transition(&tempName, loadState);
    Transition *loadTran_2 = new Transition(&tempName, validMapState);
    Transition *transitionList[] = {loadTran_1, loadTran_2};
    loadState->setTransitions(transitionList);

    tempName = "validatemap";
    Transition *validMapTran = new Transition(&tempName, loadState);

    cout << *addPlayerState->getName() << endl;
    cout << *loadState->getTransitions()->Transition::getName();
}



State *GameEngine::getCurrentState()
{
    return GameEngine::currentState;
}

void GameEngine::setCurrentState(State *currentState)
{
    GameEngine::currentState = currentState;
}















// MAIN
int main(int argc, char const *argv[])
{
    GameEngine *test = new GameEngine();

    delete test;
    return 0;
}
