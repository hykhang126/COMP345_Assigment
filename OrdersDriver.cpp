#include "Orders.h"

/**
 * Orders Driver to demonstrate specifications for Orders
*/
int main() {
    //---------------------------INITIALIZATION-----------------------------------
    cout << "Initializing list and orders........................." << endl;
    // Initialization of list
    OrdersList* list = new OrdersList();
    //Initialization of Orders
    Deploy* order1 = new Deploy(); //deploy order
    Advance* order2 = new Advance(); //advance order
    Bomb* order3 = new Bomb(); //bomb order
    Blockade* order4 = new Blockade(); //blockade order
    Airlift* order5 = new Airlift(); //airlift order
    Negotiate* order6 = new Negotiate(); //negotiate order
    Negotiate* order7 = order6; //copy constructor
    
    //---------------------INSERTING ORDERS IN THE LIST---------------------------
    cout << "\nAdding to list....................................." << endl;
    list->addOrder(order1);
    list->addOrder(order2);
    list->addOrder(order3);
    list->addOrder(order4);
    list->addOrder(order5);
    list->addOrder(order6);
    list->addOrder(order7);

    // --------------------VALIDATION AND EXECUTION------------------------------
    cout <<"\nValidating and executing..........................." << endl;
    order1->execute();
    order2->execute();
    order3->execute();
    order4->execute();
    order5->execute();
    order6->execute();
    order7->execute();

    // -------------------STREAM INSERTION OPERATOR------------------------------    
    cout << "\nDisplaying the list of orders......................" << endl;
    // Print output
    cout << *list << endl;
    cout << "RESULT: List with all order types displayed, validated and executed! Size should be 8" << endl;

    // --------------------------REMOVE METHOD-----------------------------------
    cout << "\nTesting the remove method.........................." << endl;
    list->remove(order7);
    cout << *list << endl;
    cout << "RESULT: List with removed copy order to negotiate. Size should be down from 8 to 7!" << endl;

    // ----------------------------MOVE METHOD----------------------------------
    cout << "\nTesting the move method............................" << endl;
    list->move(order4, 7);
    cout << *list << endl;
    cout << "RESULT: List with removed order after moving order to Blockade to the 7th order position" << endl;
}