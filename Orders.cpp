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
    this->ordersList = other.ordersList;
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
