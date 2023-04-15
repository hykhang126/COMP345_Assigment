#pragma once
#include "Map.h"

using namespace std;


class PlayerStrategy{


protected:
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


class Aggressive: public PlayerStrategy {
    ~Aggressive();
    friend std::ostream& operator<<(std::ostream &out, const Aggressive &Aggressive);
    Aggressive(const Aggressive&);
    Aggressive& operator =(const Aggressive&);
    void issueOrder() override;
    vector<Territory *> * toAttack() override;
    vector<Territory *> * toDefend() override;

public:
    Aggressive();

    Aggressive(Player*);
};


class Benevolent: public PlayerStrategy {
    Benevolent();
    Benevolent(Player*);
    ~Benevolent();
    friend std::ostream& operator<<(std::ostream &out, const Benevolent &Benevolent);
    Benevolent(const Benevolent&);
    Benevolent& operator =(const Benevolent&);
    void issueOrder() override;
    vector<Territory *> * toAttack() override;
    vector<Territory *> * toDefend() override;
};