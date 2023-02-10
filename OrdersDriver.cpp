#include "Orders.h"

/**
 * Orders Driver to demonstrate specifications for Orders
*/
int main() {
    // Initialization of list
    OrdersList* list = new OrdersList();
    //Initialization of Orders
    Order* order1 = new Order();
    Order* order2 = new Order();

    // Insert Orders in OrdersList
    list->addOrder(order1);
    list->addOrder(order2);

    // Print output
    cout << *list;
}