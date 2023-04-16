
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

Player* PlayerStrategy::getPlayer() const{
    return p;
}

void PlayerStrategy::setPlayer(Player* newPlayer) {
    this->p = newPlayer;
}

/**
 * Default constructor for Human player strategy
*/
Human::Human() {
    p = new Player();
}
/**
 * Param constructor for Human player strategy
*/
Human::Human(Player* player) {
    this->p = player;
}
/**
 * Destructor for Human player strategy
*/
Human::~Human() {
    delete p;
    p = NULL;
}
// returning default output
std::ostream &operator<<(ostream &out, const Human &human) {
    out << "PlayerStrategy is Human with name " << *human.p->getName() << endl;
    return out;
}
/**
 * Copy constructor for Human player strategy
*/
Human::Human(const Human& human) {
    this->p = new Player(*human.p);
}

Human &Human::operator=(const Human &human) {
    this->p = new Player(*human.p);
    return *this;
}
/**
 * list of territories Human player can attack
*/
vector<Territory*>* Human::toAttack() {
    cout << "The following territories are neighbours to the territories you own: \n";
    vector<Territory*> neighbours;
    for(Territory* t : *p->getTerritoryCollection()) {
        for(Territory* adjacentTerritory : *(t->adjacentTerritory)) {
            if(adjacentTerritory->getOwner() != p){
                neighbours.push_back(adjacentTerritory);
            }
        }    
    }
    //print out list of neighbouring territories 
    for(Territory* territory : neighbours) {
        cout << *territory->getName() << endl;
    }
    //Prompt player for priority territories
    cout << "\nPlease enter the names of the territories to be attacked in priority (separated by spaces): \n";
    string ters;
    cin.ignore();
    getline(cin, ters);
    istringstream iss(ters);
    vector<string> priorityTerritories{istream_iterator<string>{iss}, istream_iterator<string>{}};
   
    //Add territories to territories to attack
    vector<Territory*>* territoriesToAttack;
    territoriesToAttack->clear();
    for(Territory* t: neighbours) {
        for(string& pt : priorityTerritories) {        
            string territoryName = t->getName()->substr(1);
            if(*t->getName() == pt || territoryName == pt){
                territoriesToAttack->push_back(new Territory(*t));
                break;
            }
        }
    }
    cout<< "These are the territories you chose: " << endl;
    for(Territory* t: *territoriesToAttack){
        cout << *t->getName() << endl;
    }
    return territoriesToAttack;
}

vector<Territory*>* Human::toDefend() {
    //Show territories
    cout << "\nThe following territories belong to you: \n";
    for(Territory* territory : *p->getTerritoryCollection()) {
        cout << *territory->getName() << endl;
    }
    //Prompt player for priority territories
    cout << "\nPlease enter the names of the territories to be defended in priority (separated by spaces): \n";
    string ters;
    getline(cin, ters);
    istringstream iss(ters);
    vector<string> priorityTerritories{istream_iterator<string>{iss}, istream_iterator<string>{}};
    
    //Add territories to territories to defend
    vector<Territory*>* territoriesToDefend;
    territoriesToDefend->clear();
    for(Territory* t: *p->getTerritoryCollection()) {
        bool isPriority = false;
        for(string& pt: priorityTerritories) {
            if(*t->getName() == pt) {
                isPriority = true;
                break;
            }
        }
        if(isPriority) {
            territoriesToDefend->push_back(new Territory(*t));
        }
    }
    cout<< "These are the territories you chose: " << endl;
    for(Territory* t: *territoriesToDefend){
        cout << *t->getName() << endl;
    }
    return territoriesToDefend;
}

void Human::issueOrder() {

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
    if (territoriesToDefend->size() == 0){
         maxArmies = 0;
         territoryMaxArmiesIndex = 0;
         iteratorIndex = 0;
        for (Territory *territory: *defendList) {
            if (*territory->getArmies() >= maxArmies) {
                maxArmies = *territory->getArmies();
                territoriesToDefend->push_back(territory);
            }
            iteratorIndex++;
        }
    }
    return territoriesToDefend;
}

void Aggressive::issueOrder() {
    Territory *strongestTerritory = this->toDefend()->back();

    cout
            << "The following territories are list of AGGRESSIVE PLAYER " << *p->getName()
            << " territories to be defended along with how many armies they currently have: "
            << endl;
    for (auto it = p->getTerritoryCollection()->begin(); it != p->getTerritoryCollection()->end(); ++it) {
        cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
    }
    cout << "Aggressive " << *p->getName() << " currently has " << *p->getReinforcement()
         << " available armies to deploy."
         << endl;
    cout << "Aggressive " << *p->getName() << " deploying to " << *strongestTerritory->getName()
         << " their total of " << *p->getReinforcement() << " reinforcements" << endl;

    p->getOrdersList()->addOrder(new Deploy(p->getReinforcement(), strongestTerritory, p));
    int secondMaxArmies = 0;
    while (p->hasCardInHand("airlift")) {
        cout << "Starting airlift for aggressive player " << *p->getName() << endl;
        cout << "The following is a list of the territories aggressive " << *p->getName() << " owns: " << endl;
        vector<Territory *> *ownedTerritories = p->getTerritoryCollection();
        for (auto it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it) {
            cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
        }

        string srcTerritory;
        string targetTerritory;


        int iteratorIndex = 0;
        secondMaxArmies = 0;
        int secondMaxArmiesIndex = 0;
        for (Territory *territory: *p->getTerritoryCollection()) {
            if (territory->getName() == strongestTerritory->getName()) {
                iteratorIndex++;
                continue;
            } else if (*territory->getArmies() >= secondMaxArmies) {
                secondMaxArmies = *territory->getArmies();
                secondMaxArmiesIndex = iteratorIndex;
            }
            iteratorIndex++;
        };
        Territory *secondStrongestTerritory = p->getTerritoryCollection()->at(secondMaxArmiesIndex);
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
            << "The following territories are the aggressive " << *p->getName()
            << " list of territories to be defended along with how many armies they currently have: "
            << endl;
    //vector<Territory*>* defendList = this->toDefend();
    for (auto it = p->getTerritoryCollection()->begin(); it != p->getTerritoryCollection()->end(); ++it) {
        cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
    }

    cout << "\nThe following territories are aggressive " << *p->getName() << " list of territories to attack:" << endl;
    vector<Territory *> *attackList = this->toAttack();
    if (attackList->size() == 0) {

        cout << "couldn't find a suitable enemy to attack this turn for aggressive player " << *p->getName() <<endl;
    } else {
        cout<< *attackList->back()->getName() << " holding: " << *attackList->back()->getArmies() << " armies." << endl;
        cout << "adding order for aggressive player " << *p->getName() << " to attack " << *attackList->back()->getName()
             << " holding " << *attackList->back()->getArmies() << " armies with " << *strongestTerritory->getName() << " that will hold " <<
             (*strongestTerritory->getArmies()+*p->getReinforcement()+secondMaxArmies) << " armies after deploy and airlift order executed"
             << " (currently only holding " << *strongestTerritory->getArmies() << ")" << endl;
        p->getOrdersList()->addOrder(
                new Advance(new int(*strongestTerritory->getArmies()+*p->getReinforcement()+secondMaxArmies), strongestTerritory, attackList->back(), p,
                            this->p->getOrdersList()->deck));
    }
}

Aggressive::Aggressive() {
    p = new Player();
}

Aggressive::Aggressive(Player *player) {
    this->p = player;
}

Aggressive::~Aggressive() {
    delete p;
    p = NULL;
}

// returning default output
std::ostream &operator<<(ostream &out, const Aggressive &aggressive) {
    out << "PlayerStrategy is Aggressive with name " << *aggressive.p->getName() << endl;
    return out;
}

// copy constructor makes new default player (deep copy)
Aggressive::Aggressive(const Aggressive &agg) {
    this->p = new Player(*agg.p);
}

Aggressive &Aggressive::operator=(const Aggressive &agg) {
    this->p = new Player(*agg.p);
    return *this;
}

// BENEVOLENT

Benevolent::Benevolent() {
    p = new Player();
}

Benevolent::Benevolent(Player *player) {
    this->p = player;
}

Benevolent::~Benevolent() {
    delete p;
    p = NULL;
}

// returning default output
std::ostream &operator<<(ostream &out, const Benevolent &Benevolent) {
    out << "PlayerStrategy is Benevolent with name " << *Benevolent.p->getName() << endl;
    return out;
}

// copy constructor makes new default player (deep copy)
Benevolent::Benevolent(const Benevolent &ben) {
    this->p = new Player(*ben.p);
}

Benevolent &Benevolent::operator=(const Benevolent &ben) {
    this->p = new Player(*ben.p);
    return *this;
}

vector<Territory *> *Benevolent::toAttack() {
    vector<Territory *> *territoriesToAttack = new vector<Territory *>;
    return territoriesToAttack;
}

vector<Territory *> *Benevolent::toDefend() {
    vector<Territory *> *defendList = p->getTerritoryCollection();
    std::sort(defendList->begin(), defendList->end());
    return defendList;
}

void Benevolent::issueOrder() {




    vector<Territory *> *defendList = toDefend();
    cout
            << "The following territories are your list of benevolent player " << *p->getName() <<" territories to be defended along with how many armies they currently have: "
            << endl;
    for (auto it = defendList->begin(); it != defendList->end(); ++it) {
        cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
    }
    cout << "Benevolent " << *p->getName() << " currently has " << *this->p->getReinforcement() << " available armies to deploy."
         << endl;
        int *armiesToDeploy = new int(1);
        while (*p->getReinforcement()>0) {
            cout << "Benevolent player deploying 1 army to territory " << *toDefend()->front()->getName() << endl;
            int *newReinforcement = new int(*p->getReinforcement() - *armiesToDeploy);
            p->setReinforcement(newReinforcement);
            p->getOrdersList()->addOrder(new Deploy(armiesToDeploy, defendList->front(), p));
            std::sort(defendList->begin(), defendList->end());
        }

    while (p->hasCardInHand("airlift")) {
        cout << "Starting airlift for benevolent player " << *p->getName() << endl;
        cout << "The following is a list of the territories benevolent " << *p->getName() << " owns: " << endl;
        vector<Territory *> *ownedTerritories = p->getTerritoryCollection();
        for (auto it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it) {
            cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
        }


        p->getOrdersList()->addOrder(
                new Airlift(new int(1), defendList->back(),
                            defendList->front(), p));
        vector<Card *> cards = p->getHand()->getCardsInHand();
        for (Card *c: cards) {
            if (c->getType() == "airlift") {
                p->getHand()->removeCard(c);
            }
        }
    }
}

std::ostream& operator<<(ostream &out, const NeutralPlayerStrategy &neutral) {
    if(*neutral.wasAttacked) {
        out << *neutral.agStrat;
    } else {
        out << "Neutral strategy: Computer player that never issues any order. If a Neutral player is attacked, it becomes an Aggressive player." << endl;
        out << "Player info: " << endl;
        out << *neutral.getPlayer();
    }
    return out;
}

NeutralPlayerStrategy::NeutralPlayerStrategy() {
    p = new Player();
    wasAttacked = new bool(false);
    agStrat = new Aggressive();
}

NeutralPlayerStrategy::~NeutralPlayerStrategy() {
    delete wasAttacked;
//    delete agStrat;
    delete p;
}

void NeutralPlayerStrategy::issueOrder() {
    if(*p->getWasAttacked() && *wasAttacked == false) {
        *wasAttacked = true;
        cout << "   Neutral player " << *p->getName() << " was attacked! This player will now become aggressive!" << endl;
    }

    if(*wasAttacked) {
        if(agStrat->getPlayer() == nullptr) {
            agStrat->setPlayer(p);
        } else {
//            agStrat->issueOrder();
        }
    }
}

vector<Territory*>* NeutralPlayerStrategy::toAttack() {
    if(*p->getWasAttacked() && *wasAttacked == false) {
        *wasAttacked = true;
        cout << "   Neutral player " << *p->getName() << " was attacked! This player will now become aggressive!" << endl;
    }

    if(*wasAttacked) {
//      return agStrat->toAttack();
    } else {
        return new vector<Territory*>();
    }
}

vector<Territory*>* NeutralPlayerStrategy::toDefend() {
    if(*p->getWasAttacked() && *wasAttacked == false) {
        *wasAttacked = true;
        cout << "   Neutral player " << *p->getName() << " was attacked! This player will now become aggressive!" << endl;
    }

    if(*wasAttacked) {
//      return agStrat->toDefend();
    } else {
        return new vector<Territory*>();
    }
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) {
    setPlayer(p);
    this->wasAttacked = new bool(false);
    this->agStrat = new Aggressive(p);
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& other) {
    this->wasAttacked = new bool(*other.wasAttacked);
//    this->agStrat = new Aggressive(*other.agStrat);
    setPlayer(other.getPlayer());
}

NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& rhs) {
    setPlayer(rhs.getPlayer());
    this->wasAttacked = new bool(*rhs.wasAttacked);
//    this->agStrat = new Aggressive(*rhs.agStrat);
    return *this;
}

std::ostream& operator<<(ostream& out, const CheaterPlayerStrategy& cheater) {
    out << "Cheater player: compputer player that automatically conqers all territories that are adjacent to its own territories(only once per turn)" << endl;
    out << "Player info:" << endl;
    out << *cheater.getPlayer();
    return out;
}

CheaterPlayerStrategy::CheaterPlayerStrategy() : PlayerStrategy() {}

CheaterPlayerStrategy::~CheaterPlayerStrategy() {}

void CheaterPlayerStrategy::issueOrder() {
    //TO DO
}

vector<Territory*>* CheaterPlayerStrategy::toAttack() {
    vector<Territory*>* neighbours = new vector<Territory*>();
    for(Territory* t : *p->getTerritoryCollection()) {
        for(Territory* adjacentTerritory : *(t->adjacentTerritory)) {
            if(adjacentTerritory->getOwner() != p){
                neighbours->push_back(adjacentTerritory);
            }
        }    
    }
    
    return neighbours;
}

vector<Territory*>* CheaterPlayerStrategy::toDefend() {
    return p->getTerritoryCollection();
}

CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& other) : PlayerStrategy(other) {}

CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& rhs) {
    setPlayer(rhs.getPlayer());
    return *this;
}