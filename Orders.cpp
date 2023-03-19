#include "Orders.h"
#include <algorithm>
#include <sstream>

/**
 * Default constructor for Order Class
*/
Order::Order() {
    description = new string("Not Defined");
    isExecuted = new bool(false); //default execution status is false
    effect = new string("Not Defined");
    isValid = new bool(false); //default validation status is false
}
/**
 * Destructor for Order Class
*/
Order::~Order() {
    delete description;
    delete isExecuted;
    delete effect;
    delete isValid;
}
/**
 * Copy constructor for Order Class
 * @param other: the other order to copy
*/
Order::Order(const Order& other) {
    this->description = new string(*(other.description));
    this->isExecuted = new bool(*(other.isExecuted));
    this->effect = new string(*(other.effect));
    this->isValid = new bool(*(other.isValid));
}
/**
 * Assignment operator for Order Class
 * @param other: the other order assigned to
*/
Order& Order::operator= (const Order& other) {
    this->description = new string(*(other.description));
    this->isExecuted = new bool(*(other.isExecuted));
    this->effect = new string(*(other.effect));
    this->isValid = new bool(*(other.isValid));
    return *this;
}
/**
 * Stream insertion operator for Order Class
*/
ostream& operator << (ostream& out, const Order& order) {
    out << *order.description;
    if(*order.isExecuted == true) {
        out << "\n\t\tExecuted: " << *order.effect;
    }
    return out;
}
/**
 * Getter for the order description
*/
string Order::getDescription() {
    return *description;
}
/**
 * Setter for the order description
*/
void Order::setDescription(string text) {
    *description = text;
}
/**
 * Getter for order execution status
*/
bool Order::getExecStatus() {
    return *isExecuted;
}
/**
 * Setter for order execution status
*/
void Order::setExecStatus(bool status) {
    *isExecuted = status;
}
/**
 * Getter for the order effect
*/
string Order::getEffect() {
    return *effect;
}
/**
 * Setter for order effect
*/
void Order::setEffect(string text) {
    *effect = text;
}
/**
 * Getter for order validation status
*/
bool Order::getValidStatus() {
    return *isValid;
}
/**
 * Setter for order validation status
*/
void Order::setValidStatus(bool status) {
    *isValid = status;
}

string Order::stringToLog() {
    string test = getEffect();
    return "LOG: Order " +getDescription() + " executed.";
}

// ------------------- DEPLOY ORDER --------------------------
/**
 * Default constructor for Deploy Class
*/
Deploy::Deploy() {
    setDescription("deploy some armies on one of the player's territories");
    setEffect("Player armies have been placed on the player's territories");
    numReinforcements = new int(0);
    target = new Territory();
    player = new Player();
}
/**
 * Destructor for Deploy Class
*/
Deploy::~Deploy() {
    delete numReinforcements;
    delete target;
    delete player;
}
/**
 * Copy Constructor for Deploy Class
*/
Deploy::Deploy(const Deploy& other) {
    setDescription("deploy some armies on one of the player's territories");
    setEffect("Player armies have been placed on the player's territories");
    this->numReinforcements = new int(*(other.numReinforcements));
    this->target = new Territory(*(other.target));
    this->player = new Player(*(other.player));
}
/**
 * Defined constructor for Deploy
 * @param number: number of armies to deploy from reinforcement pool
 * @param targetTerr: territory to deploy to
 * @param player: player issuing the order
*/
Deploy::Deploy(int* number, Territory* targetTerr, Player* player) {
    numReinforcements = number;
    target = targetTerr;
    this->player = player;
}
/**
 * Assignment Operator for Deploy Class
*/
Deploy& Deploy::operator=(const Deploy& other) {
    return *this;
}
/**
 * Stream Insertion Operator for Deploy Class
*/
ostream& operator << (ostream& out, const Deploy& deploy) {
    out << "This is an Order of type Deploy.";
    return out;
}
/**
 * Validate method for Deploy order: sets the order's validation status to true
*/
void Deploy::validate() {
    //A2: if player doesn't own the territory, invalid order
    if(target->getOwner() != player || *(player->getReinforcement()) < *numReinforcements) {
        setValidStatus(false);
        cout << "Deploy order is invalid..." << endl;
    }
    //A2: if player owns the territory, valid order
    else if (target->getOwner() == player) {
        setValidStatus(true);
        cout << "Deploy order validated!" << endl;
    }
}
/**
 * Execute method for Deploy order:
 * -First, validates the order
 * -Then, execute the order is it is valid
*/
void Deploy::execute() {
    validate();
    if (getValidStatus() == true) {
        setExecStatus(true);
        //A2: if valid, add the number of armies to the target territory
        int* newArmies = new int(*(target->getArmies()) + *numReinforcements);
        int* newPool = new int(*(player->getReinforcement()) - *numReinforcements);
        target->setArmies(newArmies);
        player->setReinforcement(*newPool);
        cout << "Deploy order executed! New number of armies: " << *(target->getArmies()) 
            << "\nOn territory: " << *(target->getName()) 
            << "\nNew reinforcement pool: " << *(player->getReinforcement()) << endl;
        notify(this);
    }
    else {
        cout << "Deploy order failed..." << endl;
    }
}
/**
 * Getter for reinforcement number to deploy
*/
int* Deploy::getReinforcements() {
    return numReinforcements;
}
/**
 * Setter for reinforcement number to deploy
*/
void Deploy::setReinforcements(int* number) {
    numReinforcements = number;
}
/**
 * Getter for target territory to deploy to
*/
Territory* Deploy::getTarget() {
    return target;
}
/**
 * 
*/

// ------------------- ADVANCE ORDER -------------------------
/**
 * Default constructor for Advance Class
*/
Advance::Advance() {
    setDescription("advance armies from one of the player's territories to an adjacent territory");
    setEffect("Player armies have moved to an adjacent territory.");
    numUnits = new int(0);
    source = new Territory();
    target = new Territory();
    player = new Player();
}
/**
 * Destructor for Advance Class
*/
Advance::~Advance() {
    delete source;
    delete target;
    delete player;
    delete numUnits;
}
/**
 * Full constructor for the Advance order
 * @param number: the number of army units ordered to move
 * @param sourceTerr: the source territory
 * @param targetTerr: the target adjacent territory
 * @param player: the player making the order
*/
Advance::Advance(int* number, Territory* sourceTerr, Territory* targetTerr, Player* player) {
    setDescription("advance armies from one of the player's territories to an adjacent territory");
    setEffect("Player armies have moved to an adjacent territory.");
    numUnits = number;
    source = sourceTerr;
    target = targetTerr;
    this->player = player;
}
/**
 * Copy Constructor for Advance Class
*/
Advance::Advance(const Advance& other) {
    this->source = new Territory(*(other.source));
    this->target = new Territory(*(other.target));
    this->player = new Player(*(other.player));
    this->numUnits = new int(*(other.numUnits));
}
/**
 * Assignment Operator for Advance Class
*/
Advance& Advance::operator=(const Advance& other) {
    return *this;
}
/**
 * Stream Insertion Operator for Advance Class
*/
ostream& operator << (ostream& out, const Advance& advance) {
    out << "This is an Order of type Advance.";
    return out;
}
/**
 * Check if target is adjacent to source
*/
bool Advance::isAdjacent() {
    for(int i = 0; i < (source->adjacentTerritory)->size(); i++) {
        if(source->adjacentTerritory->at(i)->getName() == target->getName()) {
            return true;
        }
    }
    return false;
}
/**
 * Validate method for Advance order: sets the order's validation status to true
*/
void Advance::validate() {
    //A2: if player doesn't own source territory or target territory is not adjacent, invalid order
    if(source->getOwner() != player
        || !isAdjacent()
        || *numUnits > *(source->getArmies())) {
        setValidStatus(false);
        cout << "Advance order is invalid..." << endl;
    }
    else {
        setValidStatus(true);
        cout << "Advance order validated!" << endl;
    }
}
/**
 * Execute method for Advance order:
 * -First, validates the order
 * -Then, execute the order is it is valid
*/
void Advance::execute() {
    validate();
    if (getValidStatus() == true) {
        setExecStatus(true);
        //A2: if the target territory belongs to the player issuing the order, move the number of units
        if(target->getOwner() == player) {
            int* newSourceArmies = new int(*(source->getArmies()) - *numUnits);
            int* newTargetArmies = new int(*(target->getArmies()) + *numUnits);
            source->setArmies(newSourceArmies);
            target->setArmies(newTargetArmies);
            cout << "Advance order executed!" << endl;
            cout << *numUnits << " were moved from " << *(source->getName()) << " to " << *(target->getName()) << endl;
            cout << "New number of armies for " << *(source->getName()) << ": " << *(source->getArmies()) << endl;
            cout << "New number of armies for " << *(target->getName()) << ": " << *(target->getArmies()) << endl;
        }
        //A2: if target territory belongs to an enemy, simulate the battle
        else if(target->getOwner() != player) {
            cout << "Battle initiated......" << endl;
            int* attackUnits = new int(*(numUnits));
            int* newSourceArmies = new int(*(source->getArmies()) - *numUnits);
            source->setArmies(newSourceArmies);
            int* newTargetArmies = new int(*(target->getArmies()));
            for(int i = 0; i < *(numUnits); i++) {
                if(*newTargetArmies == 0) { //stop if target territory doesn't have any more armies
                    break;
                }
                else if (std::rand() % 101 <= 60) { //each attacking unit has 60% of killing a defending unit
                    *newTargetArmies -= 1;
                }
            }
            for(int i = 0; i < *(target->getArmies()); i++) {
                if(*attackUnits == 0) {
                    break; //stop if source territory doesn't have any more armies
                }
                else if (std::rand() % 101 <= 70) {
                    *attackUnits -= 1; //each defending unit has 70% of killing an attacking unit
                }
            }
            *newSourceArmies += *attackUnits;
            source->setArmies(newSourceArmies);
            target->setArmies(newTargetArmies);
            //if enemy is defeated, move survivors to target terr
            if(*(target->getArmies()) == 0) {
                target->setOwner(player);
                *newSourceArmies -= *attackUnits;
                *newTargetArmies += *attackUnits;
                source->setArmies(newSourceArmies);
                target->setArmies(newTargetArmies);
                cout << "Advance order executed!" << endl;
                cout << "Player " << *(source->getOwner()->getName()) << " has conquered " << *(target->getName()) << endl;
                cout << "New owner of " << *(target->getName()) << ": " << *(target->getOwner()->getName()) << endl;
                cout << "Moving " << *attackUnits << " to " << *(target->getName()) << endl;
                cout << "New army for " << *(source->getName()) << ": " << *(source->getArmies()) << endl;
                cout << "New army for " << *(target->getName()) << ": " << *(target->getArmies()) << endl;
            }
            else {
                cout << "Advance order executed!" << endl;
                cout << "New army for " << *(source->getName()) << ": " << *(source->getArmies()) << endl;
                cout << "New army for " << *(target->getName()) << ": " << *(target->getArmies()) << endl;
            }
        }
        notify(this);
    }
    else {
        cout << "Advance order failed..." << endl;
    }
}
/**
 * Getter for source territory
*/
Territory* Advance::getSource() {
    return source;
}
/**
 * Setter for source territory
*/
void Advance::setSource(Territory* sourceTerr) {
    source = sourceTerr;
}
/**
 * Getter for target territory
*/
Territory* Advance::getTarget() {
    return target;
}
/**
 * Setter for target territory
*/
void Advance::setTarget(Territory* targetTerr) {
    target = targetTerr;
}
/**
 * Getter for player
*/
Player* Advance::getPlayer() {
    return player;
}
/**
 * Setter for player
*/
void Advance::setPlayer(Player* player) {
    this->player = player;
}

// ------------------- BOMB ORDER ----------------------------
/**
 * Default constructor for Bomb Class
*/
Bomb::Bomb() {
    setDescription("bomb half of the armies on the opponent's territory that is adjacent to the player's");
    setEffect("Half of the armies on the opponent's territory has been destroyed.");
    target = new Territory();
    player = new Player();
}
/**
 * Destructor for Bomb Class
*/
Bomb::~Bomb() {
    delete target;
    delete player;
}
/**
 * Defined constructor
*/
Bomb::Bomb(Territory* targetTerr, Player* player) {
    setDescription("bomb half of the armies on the opponent's territory that is adjacent to the player's");
    setEffect("Half of the armies on the opponent's territory has been destroyed.");
    target = targetTerr;
    this->player = player;
}
/**
 * Copy Constructor for Bomb Class
*/
Bomb::Bomb(const Bomb& other) {
    this->target = new Territory(*(other.target));
    this->player = new Player(*(other.player));
}
/**
 * Assignment Operator for Bomb Class
*/
Bomb& Bomb::operator=(const Bomb& other) {
    return *this;
}
/**
 * Stream Insertion Operator for Bomb Class
*/
ostream& operator << (ostream& out, const Bomb& bomb) {
    out << "This is an Order of type Bomb.";
    return out;
}
/**
 * Check if target is adjacent to one of player's territories
*/
bool Bomb::isAdjacent() {
    for(int i = 0; i < player->getTerritoryCollection()->size(); i++) {
        for(int j = 0; j < player->getTerritoryCollection()->at(i)->adjacentTerritory->size(); i++) {
            if(player->getTerritoryCollection()->at(i)->adjacentTerritory->at(j)->getName() == target->getName()) {
                return true;
            }
        }
    }
    return false;
}
/**
 * Validate method for Bomb order: sets the order's validation status to true
*/
void Bomb::validate() {
    //if target terr is owned by player or is not adjacent to one of the player's territories, order is invalid
    if(target->getOwner() == player || !isAdjacent()) {
        setValidStatus(false);
        cout << "Bomb order is invalid..." << endl;
    }
    else {
        setValidStatus(true);
        cout << "Bomb order validated!" << endl;
    }
}
/**
 * Execute method for Bomb order:
 * -First, validates the order
 * -Then, execute the order is it is valid
*/
void Bomb::execute() {
    validate();
    if (getValidStatus() == true) {
        setExecStatus(true);
        int* newTargetArmies = new int(*(target->getArmies())/2);
        target->setArmies(newTargetArmies);
        cout << "Bomb order executed!" << endl;
        cout << "New army for " << *(target->getName()) << ": " << *(target->getArmies()) << endl;
        notify(this);
    }
    else {
        cout << "Bomb order failed..." << endl;
    }
}
/**
 * Getters and setters
*/
Territory* Bomb::getTarget() {
    return target;
}
void Bomb::setTarget(Territory* targetTerr) {
    target = targetTerr;
}
Player* Bomb::getPlayer() {
    return player;
}
void Bomb::setPlayer(Player* player) {
    this->player = player;
}

// ------------------- BLOCKADE ORDER ------------------------
/**
 * Default constructor for Blockade Class
*/
Blockade::Blockade() {
    setDescription("blockade one of the player's territories");
    setEffect("Number of armies on the player's territory has been tripled. The territory is now neutral.");
    target = new Territory();
    player = new Player();
}
/**
 * Destructor for Blockade Class
*/
Blockade::~Blockade() {
    delete target;
    delete player;
}
/**
 * Copy Constructor for Blockade Class
*/
Blockade::Blockade(const Blockade& other) {
    this->target = new Territory(*(other.target));
    this->player = new Player(*(other.player));
}
/**
 * Defined constructor
*/
Blockade::Blockade(Territory* targetTerr, Player* player) {
    target = targetTerr;
    this->player = player;
}
/**
 * Assignment Operator for Blockade Class
*/
Blockade& Blockade::operator=(const Blockade& other) {
    return *this;
}
/**
 * Stream Insertion Operator for Blockade Class
*/
ostream& operator << (ostream& out, const Blockade& blockade) {
    out << "This is an Order of type Blockade.";
    return out;
}
/**
 * Validate method for Blockade order: sets the order's validation status to true
*/
void Blockade::validate() {
    if(target->getOwner() != player) {
        setValidStatus(false);
        cout << "Blockade order is invalid..." << endl;
    }
    else {
        setValidStatus(true);
        cout << "Blockade order validated!" << endl;
    }
}
/**
 * Execute method for Blockade order:
 * -First, validates the order
 * -Then, execute the order is it is valid
*/
void Blockade::execute() {
    validate();
    if (getValidStatus() == true) {
        setExecStatus(true);
        int* newTargetArmies = new int(*(target->getArmies())*2);
        target->setArmies(newTargetArmies);
        cout << "Blockade order executed!" << endl;
        cout << "New army in " << *(target->getName()) << ": " << *(target->getArmies()) << endl;
        notify(this);
    }
    else {
        cout << "Blockade order failed..." << endl;
    }
}
/**
 * Getters and setters
*/
Territory* Blockade::getTarget() {
    return target;
}
void Blockade::setTarget(Territory* targetTerr) {
    target = targetTerr;
}
Player* Blockade::getPlayer() {
    return player;
}
void Blockade::setPlayer(Player* player) {
    this->player = player;
}


// ------------------- AIRLIFT ORDER -------------------------
/**
 * Default constructor for Airlift Class
*/
Airlift::Airlift() {
    setDescription("airlift some armies from one of the player's territories to another territory");
    setEffect("Player's armies has advanced to the target territory");
    numArmies = 0;
    source = new Territory();
    target = new Territory();
    player = new Player();
}
/**
 * Destructor for Airlift Class
*/
Airlift::~Airlift() {
    delete numArmies;
    delete source;
    delete target;
    delete player;
}
/**
 * Defined constructor
*/
Airlift::Airlift(int* number, Territory* sourceTerr, Territory* targetTerr, Player* player) {
    numArmies = number;
    source = sourceTerr;
    target = targetTerr;
    this->player = player;
}
/**
 * Copy Constructor for Airlift Class
*/
Airlift::Airlift(const Airlift& other) {
    this->numArmies = new int(*(other.numArmies));
    this->source = new Territory(*(other.source));
    this->target = new Territory(*(other.target));
    this->player = new Player(*(other.player));
}
/**
 * Assignment Operator for Airlift Class
*/
Airlift& Airlift::operator=(const Airlift& other) {
    return *this;
}
/**
 * Stream Insertion Operator for Airlift Class
*/
ostream& operator << (ostream& out, const Airlift& airlift) {
    out << "This is an Order of type Airlift.";
    return out;
}
/**
 * Validate method for Airlift order: sets the order's validation status to true
*/
void Airlift::validate() {
    //if source or target doesn't belong to player issuing order, invalid order
    if(source->getOwner() != player || target->getOwner() != player) {
        setValidStatus(false);
        cout << "Airlift order is invalid..." << endl;
    }
    else {
        setValidStatus(true);
        cout << "Airlift order validated!" << endl;
    }
}
/**
 * Execute method for Airlift order:
 * -First, validates the order
 * -Then, execute the order is it is valid
*/
void Airlift::execute() {
    validate();
    if (getValidStatus() == true) {
        setExecStatus(true);
        cout << "Airlift order executed!" << endl;
        int* newSourceArmies = new int(*(source->getArmies())- *numArmies);
        int* newTargetArmies = new int(*(target->getArmies()) + *numArmies);
        source->setArmies(newSourceArmies);
        target->setArmies(newTargetArmies);
        cout << "New army in " << *(source->getName()) << ": " << *(source->getArmies()) << endl;
        cout << "New army in " << *(target->getName()) << ": " << *(target->getArmies()) << endl;
        notify(this);
    }
    else {
        cout << "Airlift order failed..." << endl;
    }
}
/**
 * Getters and Setters
*/
int* Airlift::getNumArmies() {
    return numArmies;
}
void Airlift::setNumArmies(int* number) {
    numArmies = number;
}
Territory* Airlift::getSource() {
    return source;
}
void Airlift::setSource(Territory* sourceTerr) {
    source = sourceTerr;
}
Territory* Airlift::getTarget() {
    return target;
}
void Airlift::setTarget(Territory* targetTerr) {
    target = targetTerr;
}
Player* Airlift::getPlayer() {
    return player;
}
void Airlift::setPlayer(Player* player) {
    this->player = player;
}

// ------------------- NEGOTIATE ORDER -----------------------
/**
 * Default constructor for Negotiate Class
*/
Negotiate::Negotiate() {
    setDescription("negotiate between the current player and another player");
    setEffect("No attacks allowed between the players in negotiation until the end of the turn");
}
/**
 * Destructor for Negotiate Class
*/
Negotiate::~Negotiate() {

}
/**
 * Copy Constructor for Negotiate Class
*/
Negotiate::Negotiate(const Negotiate& other) {
    
}
/**
 * Assignment Operator for Negotiate Class
*/
Negotiate& Negotiate::operator=(const Negotiate& other) {
    return *this;
}
/**
 * Stream Insertion Operator for Negotiate Class
*/
ostream& operator << (ostream& out, const Negotiate& negotiate) {
    out << "This is an Order of type Negotiate.";
    return out;
}
/**
 * Validate method for Negotiate order: sets the order's validation status to true
*/
void Negotiate::validate() {
    setValidStatus(true);
        cout << "Negotiate order validated!" << endl;
}
/**
 * Execute method for Negotiate order:
 * -First, validates the order
 * -Then, execute the order is it is valid
*/
void Negotiate::execute() {
    validate();
    if (getValidStatus() == true) {
        setExecStatus(true);
        cout << "Negotiate order executed!" << endl;
        notify(this);
    }
    else {
        cout << "Negotiate order failed..." << endl;
    }
}



// ------------------- LIST OF ORDERS ------------------------
/**
 * Default constructor for OrdersList Class
*/
OrdersList::OrdersList() {
    ordersList = new vector<Order*> {};
}
/**
 * Destructor for OrdersList Class
*/
OrdersList::~OrdersList() {
    for(auto order : *ordersList) {
        delete order;
    }
    delete ordersList;
}
/**
 * Copy Constructor for OrdersList Class
 * @param other: the other list to copy
*/
OrdersList::OrdersList(const OrdersList& other) {
    this->ordersList = new vector<Order*>(*(other.ordersList));
}
/**
 * Assignment Operator for OrdersList Class
 * @param other: the other list assigned to
*/
OrdersList& OrdersList::operator=(const OrdersList& other) {
    this->ordersList = new vector<Order*>(*(other.ordersList));
    return *this;
}
/**
 * Stream Insertion Operator for OrdersList Class
*/
ostream& operator << (ostream& out, const OrdersList& list) {
    out << "The list has " << list.ordersList->size() << " orders" << endl;
    for(auto order : *list.ordersList) {
        out << "\tOrder: " << *order << endl;
    }
    return out;
}
/**
 * Method to add an order to the list
 * @param order: the order to add to the list
*/
void OrdersList::addOrder(Order* order) {
    cout << "Adding order to: " << *order << " to the list" << endl;
    ordersList->push_back(order);
    notify(this);
}
/**
 * Method to remove an order from the list
 * @param order: the order to be removed from the list
*/
void OrdersList::remove(Order* order) {
    cout << "Attempting to remove order to: " << *order << " from the list" << endl;
    auto index = find(ordersList->begin(), ordersList->end(), order); //first try finding the order
    if (index != ordersList->end()) { //if order found
        cout << "Removing order..." << endl;
        ordersList->erase(index);
    }
    else { //else inform that order is not in list
        cout << "Cannot find the order to remove..." << endl;
    }
}
/**
 * Method to move an order in the list.
 * @param order: the order to move in the list
 * @param newPosition: new position where the order will move to
*/
void OrdersList::move(Order* order, int newPosition) {
    cout << "Attempting to move order to: " << *order << " from the list " << 
            "to position " << newPosition << endl;
    //Check if the new position is valid
    if (newPosition <= 0 || newPosition > ordersList->size()) {
        cout << "New position is out of bounds..." << endl;
        return;
    }
    auto index = find(ordersList->begin(), ordersList->end(), order); //check if order is in the list
    if(index != ordersList->begin()) {
        cout << "Moving order to its new position..." << endl;
        ordersList->erase(index); //first erase order's initial position
        ordersList->insert(ordersList->begin() + newPosition - 1, order); //insert order in its new position
    }
    else {
        cout << "Cannot find the order to move..." << endl;
    }
}
/**
 * Getter for the list of orders
*/
vector<Order*> OrdersList::getList() {
    return *ordersList;
}
/**
 * Setter for the list of orders
*/
void OrdersList::setList(vector<Order*> list) {
    *ordersList = list;
}

string OrdersList::stringToLog() {
    std::stringstream buffer;
    buffer << *ordersList->back();
    return "LOG: Adding Order " + buffer.str() + " to ordersList";
}
