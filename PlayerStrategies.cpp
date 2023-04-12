
#include "PlayerStrategies.h"

/*
 *
 *      PlayerStrategy class
 *      Because it is an abstract virtual class, we will never create an instance of an PlayerStrategy, only classes that inherit it
 *      It can never be instantiated
 *      **For class requirements however**, we will still define all the methods and operators
 *
 */

// even though it can be instantiated, in theory a playerstrategy has a pointer to a player
// so default constructor makes a default player
PlayerStrategy::PlayerStrategy() {
    this->p = new Player();
}

// delete pointer, take care of dangling
PlayerStrategy::~PlayerStrategy() {
    delete p;
    p = NULL;
}

// returning default output
std::ostream &operator<<(ostream &out, const PlayerStrategy &PlayerStrategy) {
    out << "PlayerStrategy default output \n";
    return out;
}

// copy constructor makes new default player (deep copy)
PlayerStrategy::PlayerStrategy(const PlayerStrategy &) {
    this->p = new Player();
}

PlayerStrategy &PlayerStrategy::operator=(const PlayerStrategy &) {
    this->p = new Player();
    return *this;
}

