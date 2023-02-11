#include "Orders.h"

/**
 * Orders Driver to demonstrate specifications for Orders
*/
int main() {
    cout << "Initializing..........................................." << endl;
    // Initialization of list
    OrdersList* list = new OrdersList();
    //Initialization of Orders
    Order* order0 = new Order(); //non-defined order
    Deploy* order1 = new Deploy(); //deploy order
    Advance* order2 = new Advance(); //advance order
    Bomb* order3 = new Bomb(); //bomb order
    Blockade* order4 = new Blockade(); //blockade order
    Airlift* order5 = new Airlift(); //airlift order
    Negotiate* order6 = new Negotiate(); //negotiate order
    Negotiate* order7 = order6; //copy constructor
    
    cout << "\nAdding to list....................................." << endl;
    // Insert Orders in OrdersList
    list->addOrder(order0);
    list->addOrder(order1);
    list->addOrder(order2);
    list->addOrder(order3);
    list->addOrder(order4);
    list->addOrder(order5);
    list->addOrder(order6);
    list->addOrder(order7);

    cout <<"\nValidating and executing..........................." << endl;
    order1->execute();
    order2->execute();
    order3->execute();
    order4->execute();
    order5->execute();
    order6->execute();
    order7->execute();
    
    cout << "\nDisplaying the list of orders......................" << endl;
    // Print output
    cout << *list;
}