#include "Orders.h"

/**
 * Default constructor for Order Class
*/
Order::Order() {

}
/**
 * Destructor for Order Class
*/
Order::~Order() {
}
/**
 * Copy constructor for Order Class
 * @param other: the other order to copy
*/
Order::Order(const Order& other) {

}
/**
 * Assignment operator for Order Class
 * @param other: the other order assigned to
*/
Order& Order::operator= (const Order& other) {
    return *this;
}
/**
 * Stream insertion operator for Order Class
*/
ostream& operator << (ostream& out, const Order& order) {
    out << "Placeholder Order";
    return out;
}

// ------------------- DEPLOY ORDER --------------------------
/**
 * Default constructor for Deploy Class
*/
Deploy::Deploy() {

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

// ------------------- ADVANCE ORDER -------------------------
/**
 * Default constructor for Advance Class
*/
Advance::Advance() {

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

// ------------------- BOMB ORDER ----------------------------
/**
 * Default constructor for Bomb Class
*/
Bomb::Bomb() {

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

// ------------------- BLOCKADE ORDER ------------------------
/**
 * Default constructor for Blockade Class
*/
Blockade::Blockade() {

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

// ------------------- AIRLIFT ORDER -------------------------
/**
 * Default constructor for Airlift Class
*/
Airlift::Airlift() {

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

// ------------------- NEGOTIATE ORDER -----------------------
/**
 * Default constructor for Negotiate Class
*/
Negotiate::Negotiate() {

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
        order = NULL;
    }
    ordersList->clear();
    delete(ordersList);
    ordersList=NULL;
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
    cout << "Adding order " << *order << " to the list" << endl;
    ordersList->push_back(order);
}
