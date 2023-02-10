
#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <vector>

using namespace std;

// Specific design requirements
// 1. All data members of user-defined class type must be of pointer type.
// 2. All file names and the content of the files must be according to what is given in the 
// description below.
// 3. All different parts must be implemented in their own separate .cpp/.h file duo. All 
// functions’ implementation must be provided in the .cpp file (i.e. no inline functions are 
// allowed).
// 4. All classes must implement a correct copy constructor, assignment operator, and stream 
// insertion operator.
// 5. Memory leaks must be avoided.
// 6. Code must be documented using comments (user-defined classes, methods, free functions, operators).
// 7. If you use third-party libraries that are not available in the labs and require 
// setup/installation, you may not assume to have help using them and you are entirely responsible 
// for their proper installation for grading purposes.

/**
 * Order: User-defined class to create Order objects
*/
class Order
{
private:
    /* data */
public:
    //default constructor
    Order(/* args */);
    //destructor
    ~Order();

    //copy constructor
    Order(const Order& other);
    //assignment operator
    Order& operator = (const Order& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Order &order);
};

// ------------------- LIST OF ORDERS ------------------------
/**
 * OrdersList: User-defined class to create and manipulate lists of orders
*/
class OrdersList
{
private:
    /* data */
    vector<Order*>* ordersList;
public:
    //default constructor
    OrdersList(/* args */);
    //destructor
    ~OrdersList();

    //copy constructor
    OrdersList(const OrdersList& other);
    //assignment operator
    OrdersList& operator = (const OrdersList& other);
    //stream operator
    friend ostream& operator << (ostream& out, const OrdersList& list);

    //method to add orders to the list
    void addOrder(Order* order);
};

#endif //ORDERS_H