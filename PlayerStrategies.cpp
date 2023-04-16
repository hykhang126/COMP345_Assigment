
#include "PlayerStrategies.h"

using namespace std;
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

Player *PlayerStrategy::getPlayer() const {
    return p;
}

void PlayerStrategy::setPlayer(Player *newPlayer) {
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

/*
 *
 *      Aggressive class
 *
 */

// Returns a list of territories that can be attacked
// These are the territories that are adjacent to the territory that has the msot armies currently
vector<Territory *> *Aggressive::toAttack() {

    // First find the territory with the max armies and its index
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

    // these will be territories next to the territory with max armies
    vector<Territory *> *territoriesToAttack = new vector<Territory *>;

    // then we check the adjacent territories and only add them if they are not owned by the aggressive player
    auto adjacentTerritories = defendList->at(territoryMaxArmiesIndex)->adjacentTerritory;

    for (Territory *adjacTerritory: *adjacentTerritories) {
        if (adjacTerritory->getOwner() != p) {
            territoriesToAttack->push_back(adjacTerritory);
        }
    }
    return territoriesToAttack;
}
/**
 *
 * Returning a list of territories upon which the aggressive player will add armies
 * This is simply going to be a list of 1 territory: the one that already has the maximum amount of armies
 * But, to make it able to win, it must also be able to realize when a territory doesn't have adjacent non-owned territories anymore
 * At which point it moves their armies to the next territory that has adjacent territories that aren't his
 */
vector<Territory *> *Aggressive::toDefend() {

    vector<Territory *> *defendList = p->getTerritoryCollection();
    vector<Territory *> *territoriesToDefend = new vector<Territory *>;
    int maxArmies = 0;
    int territoryMaxArmiesIndex = 0;
    int iteratorIndex = 0;
    // Check all possible territories
    // Check that the territory has adjacent territories that aren't owned
    // If so, update the max armies, and check for max armies next iterations
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
    // If somehow we are still at size 0, that means that there are no attackable adjacent territories to any of our current territories
    // So we just return the one with max army
    if (territoriesToDefend->size() == 0) {
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

// Here we deploy, do airlift if they are in our hand and do advance
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
    // Check for the territory that has the second maximumm number of armies, we will airlift from that territory to our strongest territory
    int secondMaxArmies = 0;
    while (p->hasCardInHand("airlift")) {
        cout << "Starting airlift for aggressive player " << *p->getName() << endl;
        cout << "The following is a list of the territories aggressive " << *p->getName() << " owns: " << endl;
        vector<Territory *> *ownedTerritories = p->getTerritoryCollection();
        for (auto it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it) {
            if ((string) *(*it)->getName() == *strongestTerritory->getName()) {
                cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << " which will become "
                     << *(*it)->getArmies() + *p->getReinforcement() << " after deploy" << endl;
            } else {
                cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
            }
        }



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
        cout << " Specifically, order will be to take " << *secondStrongestTerritory->getArmies() << " from "
             << *secondStrongestTerritory->getName() << " into " << *strongestTerritory->getName() << endl;
        vector<Card *> cards = p->getHand()->getCardsInHand();
        for (Card *c: cards) {
            if (c->getType() == "airlift") {
                p->getHand()->removeCard(c);
            }
        }
    }
    // Finally take care of advancing, we send all our armies
    cout << "\nThe following territories are aggressive " << *p->getName() << " list of territories to attack:" << endl;
    vector<Territory *> *attackList = this->toAttack();
    if (attackList->size() == 0) {
        cout << "couldn't find a suitable enemy to attack this turn for aggressive player " << *p->getName() << endl;
    } else {
        cout << *attackList->back()->getName() << " holding: " << *attackList->back()->getArmies() << " armies."
             << endl;
        cout << "adding order for aggressive player " << *p->getName() << " to attack "
             << *attackList->back()->getName()
             << " holding " << *attackList->back()->getArmies() << " armies with " << *strongestTerritory->getName()
             << " that will hold " <<
             (*strongestTerritory->getArmies() + *p->getReinforcement() + secondMaxArmies)
             << " armies after deploy and airlift order executed"
             << " (currently only holding " << *strongestTerritory->getArmies() << ")" << endl;
        p->getOrdersList()->addOrder(
                new Advance(new int(*strongestTerritory->getArmies() + *p->getReinforcement() + secondMaxArmies),
                            strongestTerritory, attackList->back(), p,
                            this->p->getOrdersList()->deck));
    }
}

// Default  constructor, make its own player
Aggressive::Aggressive() {
    p = new Player();
}

// Constructor with an existing player, should be more used
Aggressive::Aggressive(Player *player) {
    this->p = player;
}

// Destructor, take care of dangling pointers
Aggressive::~Aggressive() {
    delete p;
    p = NULL;
}

// Returning Aggressive player with their name
std::ostream &operator<<(ostream &out, const Aggressive &aggressive) {
    out << "PlayerStrategy is Aggressive with name " << *aggressive.p->getName() << endl;
    return out;
}

// Copy constructor makes new aggressive player (deep copy)
Aggressive::Aggressive(const Aggressive &agg) {
    this->p = new Player(*agg.p);
}
// Same thing for assignment operator
Aggressive &Aggressive::operator=(const Aggressive &agg) {
    this->p = new Player(*agg.p);
    return *this;
}

/*
 *
 *      Benevolent class
 *
 */
// Default constructor, make new default player
Benevolent::Benevolent() {
    p = new Player();
}

// Constructor with existing player
Benevolent::Benevolent(Player *player) {
    this->p = player;
}

// Typical destructor
Benevolent::~Benevolent() {
    delete p;
    p = NULL;
}

// Returning benevolent type and name
std::ostream &operator<<(ostream &out, const Benevolent &Benevolent) {
    out << "PlayerStrategy is Benevolent with name " << *Benevolent.p->getName() << endl;
    return out;
}

// copy constructor makes new benevolent player (deep copy)
Benevolent::Benevolent(const Benevolent &ben) {
    this->p = new Player(*ben.p);
}

// same thing for assignment
Benevolent &Benevolent::operator=(const Benevolent &ben) {
    this->p = new Player(*ben.p);
    return *this;
}

// A benevolent player never attacks other territories
vector<Territory *> *Benevolent::toAttack() {
    vector<Territory *> *territoriesToAttack = new vector<Territory *>;
    return territoriesToAttack;
}

// For this, we sort the territories by their number of armies and return it (descending order => back has the lowest number of armies)
vector<Territory *> *Benevolent::toDefend() {
    vector<Territory *> *defendList = p->getTerritoryCollection();
    std::sort(defendList->begin(), defendList->end(), [](const auto &lhs, const auto &rhs) {
        return *lhs->getArmies() > *rhs->getArmies();
    });
//    std::sort(*defendList->begin(), *defendList->end());
    return defendList;
}

// We deploy, airlift
// We deploy 1 army at a time, and only ever airlift 1 army at a time to make sure we always focus on the weakest territories at any point in time
// In accordance with the typical gameplay loop of Warzone
void Benevolent::issueOrder() {

    // Return descending sorted list of territories
    vector<Territory *> *defendList = toDefend();
    cout
            << "The following territories are your list of benevolent player " << *p->getName()
            << " territories to be defended along with how many armies they currently have: "
            << endl;

    // Simulate a dictionary with two vectors
    // Dictionary holds name of territories and how many deployed armies the benevolent player plans to do
    vector<string> territoriesName;
    vector<int> territoriesDeployedArmies;
    // Initialize dictionary, and print current territories
    for (auto it = defendList->begin(); it != defendList->end(); ++it) {
        cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << endl;
        territoriesName.push_back(*(*it)->getName());
        territoriesDeployedArmies.push_back(0);
    }
    cout << "Benevolent " << *p->getName() << " currently has " << *this->p->getReinforcement()
         << " available armies to deploy."
         << endl;
    int *armiesToDeploy = new int(1);

    // Deploy 1 army at a time until there are no armies left
    while (*p->getReinforcement()>0) {
        // The weakest territory will initially be at the back
        cout << "Benevolent player deploying " << *armiesToDeploy << " armies to weakest territory "
             << *defendList->back()->getName() << endl;

        // We deploy 1 army, so now there is 1 less reinforcement
        p->getOrdersList()->addOrder(new Deploy(armiesToDeploy, defendList->back(), p));
        p->setReinforcement(new int(*p->getReinforcement() -1));
        // Keep track of how many deployed armies are put in that territory for future needs
        // This is because adding an order doesn't actually update the army values, we need to keep track of the army values somewhere
        for (int i = 0; i<territoriesName.size(); i++){
            if(territoriesName.at(i) == *defendList->back()->getName()){
                territoriesDeployedArmies.at(i)++;
            }
        }
        // Then we can re-sort the list of territories taking into account the added number of territories (that haven't been deployed yet but will be when orderlist executes it)
        // Find the index for the left part and add its current non-updated armies to the number of updated armies using the index
        // Do the same for the right part
        std::sort(defendList->begin(), defendList->end(), [this, &territoriesName,&territoriesDeployedArmies](const auto &lhs, const auto &rhs) {
            for (int i = 0; i<territoriesName.size(); i++){
                if(territoriesName.at(i) == *lhs->getName()){
                    for (int y = 0; y<territoriesName.size(); y++){
                        if(territoriesName.at(y) == *rhs->getName())
                            return (*lhs->getArmies() + territoriesDeployedArmies.at(i)) > (*rhs->getArmies()+territoriesDeployedArmies.at(y));
                    }
                }
            }
        });
    }

    // Airlift simply adds 1 army from the strongest to the weakest territory
    // Simply sort and send from front to back
    while (p->hasCardInHand("airlift")) {
        cout << "Starting airlift for benevolent player " << *p->getName() << endl;
        cout << "The following is a list of the territories benevolent " << *p->getName() << " owns: " << endl;
        vector<Territory *> *ownedTerritories = p->getTerritoryCollection();
        for (auto it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it) {
            for (int i =0; i<territoriesName.size(); i++){
                if (territoriesName.at(i) == *(*it)->getName()) {
                    cout << *(*it)->getName() << ", Armies: " << *(*it)->getArmies() << " which will become "
                         << *(*it)->getArmies() + territoriesDeployedArmies.at(i) << " after deploy" << endl;
                }
            }
        }
        std::sort(defendList->begin(), defendList->end(), [this](const auto &lhs, const auto &rhs) {
            if (*lhs->getName() == *toDefend()->back()->getName()) {
                return (*lhs->getArmies() + *p->getReinforcement()) > *rhs->getArmies();
            } else if (*rhs->getName() == *toDefend()->back()->getName()) {
                return (*lhs->getArmies()) > (*rhs->getArmies() + *p->getReinforcement());
            } else
                return *lhs->getArmies() > *rhs->getArmies();
        });

        p->getOrdersList()->addOrder(
                new Airlift(new int(1), defendList->front(),
                            defendList->back(), p));
        cout << " Specifically, order will be to take 1 army " << " from " << *defendList->front()->getName()
             << " into " << *defendList->back()->getName() << endl;

        vector<Card *> cards = p->getHand()->getCardsInHand();
        for (Card *c: cards) {
            if (c->getType() == "airlift") {
                p->getHand()->removeCard(c);
            }
        }
    }
}

std::ostream &operator<<(ostream &out, const NeutralPlayerStrategy &neutral) {
    if (*neutral.wasAttacked) {
        out << *neutral.agStrat;
    } else {
        out
                << "Neutral strategy: Computer player that never issues any order. If a Neutral player is attacked, it becomes an Aggressive player."
                << endl;
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
    if (*p->getWasAttacked() && *wasAttacked == false) {
        *wasAttacked = true;
        cout << "   Neutral player " << *p->getName() << " was attacked! This player will now become aggressive!"
             << endl;
    }

    if (*wasAttacked) {
        if (agStrat->getPlayer() == nullptr) {
            agStrat->setPlayer(p);
        } else {
//            agStrat->issueOrder();
        }
    }
}

vector<Territory *> *NeutralPlayerStrategy::toAttack() {
    if (*p->getWasAttacked() && *wasAttacked == false) {
        *wasAttacked = true;
        cout << "   Neutral player " << *p->getName() << " was attacked! This player will now become aggressive!"
             << endl;
    }

    if (*wasAttacked) {
//      return agStrat->toAttack();
    } else {
        return new vector<Territory *>();
    }
}

vector<Territory *> *NeutralPlayerStrategy::toDefend() {
    if (*p->getWasAttacked() && *wasAttacked == false) {
        *wasAttacked = true;
        cout << "   Neutral player " << *p->getName() << " was attacked! This player will now become aggressive!"
             << endl;
    }

    if (*wasAttacked) {
//      return agStrat->toDefend();
    } else {
        return new vector<Territory *>();
    }
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p) {
    setPlayer(p);
    this->wasAttacked = new bool(false);
    this->agStrat = new Aggressive(p);
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy &other) {
    this->wasAttacked = new bool(*other.wasAttacked);
//    this->agStrat = new Aggressive(*other.agStrat);
    setPlayer(other.getPlayer());
}

NeutralPlayerStrategy &NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy &rhs) {
    setPlayer(rhs.getPlayer());
    this->wasAttacked = new bool(*rhs.wasAttacked);
//    this->agStrat = new Aggressive(*rhs.agStrat);
    return *this;
}

std::ostream &operator<<(ostream &out, const CheaterPlayerStrategy &cheater) {
    out
            << "Cheater player: compputer player that automatically conqers all territories that are adjacent to its own territories(only once per turn)"
            << endl;
    out << "Player info:" << endl;
    out << *cheater.getPlayer();
    return out;
}

CheaterPlayerStrategy::CheaterPlayerStrategy() : PlayerStrategy() {}

CheaterPlayerStrategy::~CheaterPlayerStrategy() {}

void CheaterPlayerStrategy::issueOrder() {
    //TO DO
}

vector<Territory *> *CheaterPlayerStrategy::toAttack() {
    vector<Territory *> *neighbours = new vector<Territory *>();
    for (Territory *t: *p->getTerritoryCollection()) {
        for (Territory *adjacentTerritory: *(t->adjacentTerritory)) {
            if (adjacentTerritory->getOwner() != p) {
                neighbours->push_back(adjacentTerritory);
            }
        }
    }

    return neighbours;
}

vector<Territory *> *CheaterPlayerStrategy::toDefend() {
    return p->getTerritoryCollection();
}

CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy &other) : PlayerStrategy(other) {}

CheaterPlayerStrategy &CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy &rhs) {
    setPlayer(rhs.getPlayer());
    return *this;
}