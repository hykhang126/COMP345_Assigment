#include "Orders.h"

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

// ------------------- DEPLOY ORDER --------------------------
/**
 * Default constructor for Deploy Class
*/
Deploy::Deploy() {
    setDescription("deploy some armies on one of the player's territories");
    setEffect("Player armies have been placed on the player's territories");
}
/**
 * Destructor for Deploy Class
*/
Deploy::~Deploy() {

}
/**
 * Copy Constructor for Deploy Class
*/
Deploy::Deploy(const Deploy& other) {
    
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
    setValidStatus(true);
        cout << "Deploy order validated!" << endl;
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
        cout << "Deploy order executed!" << endl;
    }
    else {
        cout << "Deploy order failed..." << endl;
    }
}

// ------------------- ADVANCE ORDER -------------------------
/**
 * Default constructor for Advance Class
*/
Advance::Advance() {
    setDescription("advance armies from one of the player's territories to an adjacent territory");
    setEffect("Player armies have moved to an adjacent territory.");
}
/**
 * Destructor for Advance Class
*/
Advance::~Advance() {

}
/**
 * Copy Constructor for Advance Class
*/
Advance::Advance(const Advance& other) {
    
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
 * Validate method for Advance order: sets the order's validation status to true
*/
void Advance::validate() {
    setValidStatus(true);
        cout << "Advance order validated!" << endl;
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
        cout << "Advance order executed!" << endl;
    }
    else {
        cout << "Advance order failed..." << endl;
    }
}


// ------------------- BOMB ORDER ----------------------------
/**
 * Default constructor for Bomb Class
*/
Bomb::Bomb() {
    setDescription("bomb half of the armies on the opponent's territory that is adjacent to the player's");
    setEffect("Half of the armies on the opponent's territory has been destroyed.");
}
/**
 * Destructor for Bomb Class
*/
Bomb::~Bomb() {

}
/**
 * Copy Constructor for Bomb Class
*/
Bomb::Bomb(const Bomb& other) {
    
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
 * Validate method for Bomb order: sets the order's validation status to true
*/
void Bomb::validate() {
    setValidStatus(true);
        cout << "Bomb order validated!" << endl;
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
        cout << "Bomb order executed!" << endl;
    }
    else {
        cout << "Bomb order failed..." << endl;
    }
}


// ------------------- BLOCKADE ORDER ------------------------
/**
 * Default constructor for Blockade Class
*/
Blockade::Blockade() {
    setDescription("blockade one of the player's territories");
    setEffect("Number of armies on the player's territory has been tripled. The territory is now neutral.");
}
/**
 * Destructor for Blockade Class
*/
Blockade::~Blockade() {

}
/**
 * Copy Constructor for Blockade Class
*/
Blockade::Blockade(const Blockade& other) {
    
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
    setValidStatus(true);
        cout << "Blockade order validated!" << endl;
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
        cout << "Blockade order executed!" << endl;
    }
    else {
        cout << "Blockade order failed..." << endl;
    }
}


// ------------------- AIRLIFT ORDER -------------------------
/**
 * Default constructor for Airlift Class
*/
Airlift::Airlift() {
    setDescription("airlift some armies from one of the player's territories to another territory");
    setEffect("Player's armies has advanced to the target territory");
}
/**
 * Destructor for Airlift Class
*/
Airlift::~Airlift() {

}
/**
 * Copy Constructor for Airlift Class
*/
Airlift::Airlift(const Airlift& other) {
    
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
    setValidStatus(true);
        cout << "Airlift order validated!" << endl;
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
    }
    else {
        cout << "Airlift order failed..." << endl;
    }
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
}
/**
 * Method to remove an order from the list
 * @param order: the order to be removed from the list
*/
void OrdersList::remove(Order* order) {
    cout << "Attempting to remove order to: " << *order << " from the list" << endl;
    auto index = find(ordersList->begin(), ordersList->end(), order);
    if (index != ordersList->end()) {
        cout << "Removing order..." << endl;
        ordersList->erase(index);
    }
    else {
        cout << "Cannot find the order to remove..." << endl;
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