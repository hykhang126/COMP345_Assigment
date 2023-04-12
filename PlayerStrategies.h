#pragma once
#include "Map.h"

using namespace std;


class PlayerStrategy{
private :
    Player * p;


public :
    virtual void issueOrder() = 0;
    virtual vector<Territory*>* toAttack() = 0;
    virtual vector<Territory*>* toDefend() = 0;
    PlayerStrategy();
    ~PlayerStrategy();
    friend std::ostream& operator<<(std::ostream &out, const PlayerStrategy &PlayerStrategy);
    PlayerStrategy(const PlayerStrategy&);
    PlayerStrategy& operator =(const PlayerStrategy&);
};

class Human : public PlayerStrategy {

};