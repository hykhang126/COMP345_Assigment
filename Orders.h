
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
 * Types of Orders: Deploy
 *                  
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
    friend ostream& operator << (ostream& out, const Order& order);
};

// ------------------- DEPLOY ORDER --------------------------
/**
 * Deploy: user-defined subclass and one type of Order.
*/
class Deploy : public Order
{
private:
    /* data */
public:
    //default constructor
    Deploy(/* args */);
    //destructor
    ~Deploy();

    //copy constructor
    Deploy(const Deploy& other);
    //assignment operator
    Deploy& operator = (const Deploy& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Deploy& deploy);
};

// ------------------- ADVANCE ORDER -------------------------
/**
 * Advance: user-defined subclass and one type of Order.
*/
class Advance : public Order
{
private:
    /* data */
public:
    //default constructor
    Advance(/* args */);
    //destructor
    ~Advance();

    //copy constructor
    Advance(const Advance& other);
    //assignment operator
    Advance& operator = (const Advance& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Advance& advance);
};

// ------------------- BOMB ORDER ----------------------------
/**
 * Bomb: user-defined subclass and one type of Order
*/
class Bomb : public Order
{
private:
    /* data */
public:
    //default constructor
    Bomb(/* args */);
    //destructor
    ~Bomb();

    //copy constructor
    Bomb(const Bomb& other);
    //assignment operator
    Bomb& operator = (const Bomb& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Bomb& bomb);
};

// ------------------- Blockade ORDER ------------------------
/**
 * Blockade: user-defined subclass and one type of Order
*/
class Blockade : public Order
{
private:
    /* data */
public:
    //default constructor
    Blockade(/* args */);
    //destructor
    ~Blockade();

    //copy constructor
    Blockade(const Blockade& other);
    //assignment operator
    Blockade& operator = (const Blockade& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Blockade& blockade);
};

// ------------------- AIRLIFT ORDER -------------------------
/**
 * Airlift: subclass and one type of Order
*/
class Airlift : public Order
{
private:
    /* data */
public:
    //default constructor
    Airlift(/* args */);
    //destructor
    ~Airlift();

    //copy constructor
    Airlift(const Airlift& other);
    //assignment operator
    Airlift& operator = (const Airlift& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Airlift& airlift);
};

// ------------------- NEGOTIATE ORDER -----------------------
/**
 * Negotiate: user-defined subclass and one type of Order
*/
class Negotiate : public Order
{
private:
    /* data */
public:
    //default constructor
    Negotiate(/* args */);
    //destructor
    ~Negotiate();

    //copy constructor
    Negotiate(const Negotiate& other);
    //assignment operator
    Negotiate& operator = (const Negotiate& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Negotiate& negotiate);
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

    //getter
    vector<Order*> getList();
    //setter
    void setList(vector<Order*> list);
};

#endif //ORDERS_H
