#include "Orders.h"

/**
 * Orders Driver to demonstrate specifications for Orders
*/
int main() {
    // Initialization of list
    OrdersList* list = new OrdersList();
    //Initialization of Orders
    Order* order0 = new Order(); //non-defined order
    Order* order1 = new Deploy(); //deploy order
    Order* order2 = new Advance(); //advance order
    Order* order3 = new Bomb(); //bomb order
    Order* order4 = new Blockade(); //blockade order
    Order* order5 = new Airlift(); //airlift order
    Order* order6 = new Negotiate(); //negotiate order
    Order* order7 = order3; //copy constructor
    

    // Insert Orders in OrdersList
    list->addOrder(order0);
    list->addOrder(order1);
    list->addOrder(order2);
    list->addOrder(order3);
    list->addOrder(order4);
    list->addOrder(order5);
    list->addOrder(order6);
    list->addOrder(order7);

    //Testing if executed orders will output effect
    order0->setExecStatus(true);
    order1->setExecStatus(true);
    order2->setExecStatus(true);
    order3->setExecStatus(true);
    order4->setExecStatus(true);
    order5->setExecStatus(true);
    order6->setExecStatus(true);
    order7->setExecStatus(true);

    

    // Print output
    cout << *list;
}