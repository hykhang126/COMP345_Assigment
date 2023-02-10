#include "Orders.h"

/**
 * Orders Driver to demonstrate specifications for Orders
*/
int main() {
    // Initialization of list
    OrdersList* list = new OrdersList();
    //Initialization of Orders
    Order* order0 = new Order();
    Order* order1 = new Deploy();
    Order* order2 = new Advance();
    Order* order3 = new Bomb();
    Order* order4 = new Blockade();
    Order* order5 = new Airlift();
    Order* order6 = new Negotiate();
    

    // Insert Orders in OrdersList
    list->addOrder(order0);
    list->addOrder(order1);
    list->addOrder(order2);
    list->addOrder(order3);
    list->addOrder(order4);
    list->addOrder(order5);
    list->addOrder(order6);
    

    // Print output
    cout << *list;
}