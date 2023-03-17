#include "GameEngine.h"

#include <iostream>
#include <algorithm>

#include "Map.h"
#include "Player.h"
#include "Cards.h"

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

void GameEngine::initialization()
{
    // Create all states 
    startState = new State(new string("Start"));
    loadState = new State(new string("Map Loaded"));
    validMapState = new State(new string("Map Validated"));
    playersAddedState = new State(new string("Players Added"));
    assignReinState = new State(new string("Assign Reinforcement"));
    issueOrderState = new State(new string("Issue Order"));
    executeOrderState = new State(new string("Execute Order"));
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

GameEngine::~GameEngine()
{
    for (State* trans : stateList)
    {
        trans->~State();
        delete trans;
    }
    
}

bool GameEngine::isCommandValid(string *command)
{
    // cout << "-----------------------------\n";
    // cout << "Current State and its transitions:\n - ";
    // currentState->showTransitions();
    // cout << "Your command: " << *command;
    // cout << endl;

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

void GameEngine::startupPhase(Command *command)
{
    Map* map;
    MapLoader loader;
    string choice = *command->getName();

    if (choice.compare("loadmap germany") == 0)
    {
        string mapName = choice.substr(9);
        map = loader.loadMapFromFile(choice);
    }
    else if (choice.compare("validate") == 0)
    {
        map->validate();
    }
    else if (choice.compare("addplayer") == 0)
    {

    }
    else if (choice.compare("gamestart") == 0)
    {
        
    }
    
}











