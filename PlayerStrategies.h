#pragma once
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

class Deck;

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
    Player* getPlayer() const;
    void setPlayer(Player* newPlayer);
};

class Human : public PlayerStrategy {
    public:
        Human();
        Human(Player*);
        ~Human();
        friend std::ostream& operator<<(std::ostream &out, const Human &Human);
        Human(const Human&);
        Human& operator =(const Human&);
        void issueOrder() override;
        vector<Territory *> * toAttack() override;
        vector<Territory *> * toDefend() override;
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

    ~Benevolent();
    friend std::ostream& operator<<(std::ostream &out, const Benevolent &Benevolent);
    Benevolent(const Benevolent&);
    Benevolent& operator =(const Benevolent&);
    void issueOrder() override;
    vector<Territory *> * toAttack() override;
    vector<Territory *> * toDefend() override;

public:
    Benevolent(Player*);
};


class NeutralPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder() override;
        void issueOrder(vector<Player*>* gamePlayers, Deck* deck);
        vector<Territory*>* toAttack() override;
        vector<Territory*>* toDefend() override;
        NeutralPlayerStrategy();
        NeutralPlayerStrategy(Player* p);
        ~NeutralPlayerStrategy();
        friend std::ostream& operator<<(std::ostream &out, const NeutralPlayerStrategy &neutral);
        NeutralPlayerStrategy(const NeutralPlayerStrategy&);
        NeutralPlayerStrategy& operator =(const NeutralPlayerStrategy&);
    
    private:
        bool* wasAttacked;
};

class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        void issueOrder() override;
        vector<Territory*>* toAttack() override;
        vector<Territory*>* toDefend() override;
        CheaterPlayerStrategy();
        CheaterPlayerStrategy(Player* p);
        ~CheaterPlayerStrategy();
        friend std::ostream& operator<<(std::ostream &out, const CheaterPlayerStrategy &Cheater);
        CheaterPlayerStrategy(const CheaterPlayerStrategy&);
        CheaterPlayerStrategy& operator =(const CheaterPlayerStrategy&);
};