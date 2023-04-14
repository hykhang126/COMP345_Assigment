
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

vector<Territory *> *Aggressive::toAttack() {

    vector<Territory *> *defendList = p->getTerritoryCollection();
    int maxArmies = 0;
    int territoryMaxArmiesIndex = 0;
    int iteratorIndex = 0;
    for (Territory *territory: *defendList) {
        if (*territory->getArmies() >= maxArmies) {
            for (Territory *adjacTerritory: *territory->adjacentTerritory)
                if (adjacTerritory->getOwner() != p) {
                    maxArmies = *territory->getArmies();
                    territoryMaxArmiesIndex = iteratorIndex;
                    break;
                }
        }
        iteratorIndex++;
    }

    vector<Territory *> *territoriesToAttack = new vector<Territory *>;

    auto adjacentTerritories = defendList->at(territoryMaxArmiesIndex)->adjacentTerritory;

    for (Territory *adjacTerritory: *adjacentTerritories) {
        if (adjacTerritory->getOwner() != p) {
            territoriesToAttack->push_back(adjacTerritory);
        }
    }
    return territoriesToAttack;
}

vector<Territory *> *Aggressive::toDefend() {

    vector<Territory *> *defendList = p->getTerritoryCollection();
    vector<Territory *> *territoriesToDefend = new vector<Territory *>;
    int maxArmies = 0;
    int territoryMaxArmiesIndex = 0;
    int iteratorIndex = 0;
    for (Territory *territory: *defendList) {
        if (*territory->getArmies() >= maxArmies) {
            for (Territory *adjacTerritory: *territory->adjacentTerritory)
                if (adjacTerritory->getOwner() != p) {
                    maxArmies = *territory->getArmies();
                    territoryMaxArmiesIndex = iteratorIndex;
                    territoriesToDefend->push_back(territory);
                    break;
                }
        }
        iteratorIndex++;
    }
    return territoriesToDefend;
}

void Aggressive::issueOrder() {
    Territory *strongestTerritory = this->toDefend()->back();

    cout
            << "The following territories are list of AGGRESSIVE PLAYER " << p->getName()
            << " territories to be defended along with how many armies they currently have: "
            << endl;
    for (auto it = p->getTerritoryCollection()->begin(); it != p->getTerritoryCollection()->end(); ++it) {
        cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
    }
    cout << "Aggressive " << p->getName() << " currently has " << *p->getReinforcement()
         << " available armies to deploy."
         << endl;
    cout << "Aggressive " << p->getName() << " deploying to " << strongestTerritory
         << " their total of " << p->getReinforcement() << " reinforcements";

    p->getOrdersList()->addOrder(new Deploy(p->getReinforcement(), strongestTerritory, p));

    while (p->hasCardInHand("airlift")) {
        cout << "Starting airlift for aggressive player " << p->getName() << endl;
        cout << "The following is a list of the territories aggressive " << p->getName() << " owns: " << endl;
        vector<Territory *> *ownedTerritories = p->getTerritoryCollection();
        for (auto it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it) {
            cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
        }

        string srcTerritory;
        string targetTerritory;


        int iteratorIndex = 0;
        int secondMaxArmies = 0;
        int secondMaxArmiesIndex = 0;
        for (Territory *territory: p->getTerritoryCollection()) {
            if (territory->getName()==strongestTerritory->getName()) {
                iteratorIndex++;
                continue;
            } else if (*territory->getArmies() >= secondMaxArmies) {
                secondMaxArmies = *territory->getArmies();
                secondMaxArmiesIndex = iteratorIndex;
            }
            iteratorIndex++;
        };
        Territory* secondStrongestTerritory = p->getTerritoryCollection()->at(secondMaxArmiesIndex);
        p->getOrdersList()->addOrder(
                new Airlift(secondStrongestTerritory->getArmies(), secondStrongestTerritory,
                            strongestTerritory, p));
        vector<Card *> cards = p->getHand()->getCardsInHand();
        for (Card *c: cards) {
            if (c->getType() == "airlift") {
                p->getHand()->removeCard(c);
            }
        }
    }
    // attacking
    cout
            << "The following territories are the aggressive " << p->getName()
            << " list of territories to be defended along with how many armies they currently have: "
            << endl;
    //vector<Territory*>* defendList = this->toDefend();
    for (auto it = p->getTerritoryCollection()->begin(); it != p->getTerritoryCollection()->end(); ++it) {
        cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
    }

    cout << "\nThe following territories are aggressive " << p->getName() << " list of terrirotires to attack:" << endl;
    vector<Territory *> *attackList = this->toAttack();
    if (attackList->size() == 0){

        cout << "couldn't find a suitable enemy to attack this turn for aggressive player " << p->getName();
    }

    else{
        cout << "adding order for aggressive player " << p->getName() << " to attack " << attackList->back()->getName() << " with " << strongestTerritory->getName();
        p->getOrdersList()->addOrder(
                new Advance(strongestTerritory->getArmies(), strongestTerritory, attackList->back(), p, this->p->getOrdersList()->deck));
    }

}

