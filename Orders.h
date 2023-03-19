
#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <vector>
#include "LoggingObserver.h"
#include "Player.h"
#include "Map.h"

//A2
using namespace std;

class Player;
class Territory;

/**
 * Order: User-defined abstract class
 * Types of Orders: Deploy, Advance, Airlift, Bomb, Blockade, and Negotiate
 * Pure Virtual Method: execute()                 
*/
class Order : public Subject, public ILoggable
{
private:
    /* data */
    string* description; //Specifies the type of Order
    bool* isExecuted; //Status of Order execution (Executed: true. Not executed: false)
    string* effect; // Specifies the effect of the Order
    bool* isValid; //Status of Order Validation (Valid: true. Not Valid: false)
public:
    //default constructor
    Order();
    //destructor
    ~Order();

    //copy constructor
    Order(const Order& other);
    //assignment operator
    Order& operator = (const Order& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Order& order);

    //A2: pure virtual method: execute()
    virtual void execute() = 0;

    //getter for order type
    string getDescription();
    //setter for order type
    void setDescription(string text);
    //getter for execution status
    bool getExecStatus();
    //setter for execution status
    void setExecStatus(bool status);
    //getter for the order effect
    string getEffect();
    //setter for order effect
    void setEffect(string text);
    //getter for order validation status
    bool getValidStatus();
    //setter for order validation status
    void setValidStatus(bool status);


    string stringToLog() override;
};

// ------------------- DEPLOY ORDER --------------------------
/**
 * Deploy: user-defined subclass and one type of Order.
*/
class Deploy : public Order
{
private:
    /* data */
    int* numReinforcements;
    Territory* target;
    Player* player;
public:
    //default constructor
    Deploy();
    //destructor
    ~Deploy();
    //defined constructor
    Deploy(int* number, Territory* targetTerr, Player* player);
    //copy constructor
    Deploy(const Deploy& other);
    //assignment operator
    Deploy& operator = (const Deploy& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Deploy& deploy);

    //validate method to make the order valid
    void validate();
    //execute method to execute an order
    void execute() override ;

    int* getReinforcements();
    void setReinforcements(int* number);
    Territory* getTarget();
    void setTarget(Territory* targetTerr);
    Player* getPlayer();
    Player* setPlayer(Player* player);
};

// ------------------- ADVANCE ORDER -------------------------
/**
 * Advance: user-defined subclass and one type of Order.
*/
class Advance : public Order
{
private:
    /* data */
    Territory* source;
    Territory* target;
    Player* player;
    int* numUnits;
public:
    //default constructor
    Advance();
    //destructor
    ~Advance();
    //defined constructor
    Advance(int* number, Territory* sourceTerr, Territory* targetTerr, Player* player);

    //copy constructor
    Advance(const Advance& other);
    //assignment operator
    Advance& operator = (const Advance& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Advance& advance);

    //check if target is adjacent to source
    bool isAdjacent();
    //check if target is of negotiating party
    bool isNegotiate();
    //validate method to make the order valid
    void validate();
    //execute method to execute an order
    void execute() override;

    //getter for source territory
    Territory* getSource();
    //setter for source territory
    void setSource(Territory* sourceTerr);
    //getter for target territory
    Territory* getTarget();
    //setter for target territory
    void setTarget(Territory* targetTerr);
    //getter for player
    Player* getPlayer();
    //setter for player
    void setPlayer(Player* player);
    //getter for number of army units
    int* getNumUnits();
    //setter for number of army units
    void setNumUnits(int* number);
};

// ------------------- BOMB ORDER ----------------------------
/**
 * Bomb: user-defined subclass and one type of Order
*/
class Bomb : public Order
{
private:
    /* data */
    Territory* target;
    Player* player;
public:
    //default constructor
    Bomb();
    //destructor
    ~Bomb();
    //defined constructor
    Bomb(Territory* targetTerr, Player* player);

    //copy constructor
    Bomb(const Bomb& other);
    //assignment operator
    Bomb& operator = (const Bomb& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Bomb& bomb);

    //check if target is adjacent to one of the player's territories
    bool isAdjacent();
    //validate method to make the order valid
    void validate();
    //execute method to execute an order
    void execute() override;

    //getters and setters
    Territory* getTarget();
    void setTarget(Territory* targetTerr);
    Player* getPlayer();
    void setPlayer(Player* player);
};

// ------------------- Blockade ORDER ------------------------
/**
 * Blockade: user-defined subclass and one type of Order
*/
class Blockade : public Order
{
private:
    /* data */
    Territory* target;
    Player* player;
public:
    //default constructor
    Blockade();
    //destructor
    ~Blockade();
    //defined constructor
    Blockade(Territory* targetTerr, Player* player);

    //copy constructor
    Blockade(const Blockade& other);
    //assignment operator
    Blockade& operator = (const Blockade& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Blockade& blockade);

    //validate method to make the order valid
    void validate();
    //execute method to execute an order
    void execute() override;

    //getters and setters
    Territory* getTarget();
    void setTarget(Territory* targetTerr);
    Player* getPlayer();
    void setPlayer(Player* player);
};

// ------------------- AIRLIFT ORDER -------------------------
/**
 * Airlift: subclass and one type of Order
*/
class Airlift : public Order
{
private:
    /* data */
    int* numArmies;
    Territory* source;
    Territory* target;
    Player* player;
public:
    //default constructor
    Airlift();
    //destructor
    ~Airlift();
    //defined constructor
    Airlift(int* number, Territory* sourceTerr, Territory* targetTerr, Player* player);

    //copy constructor
    Airlift(const Airlift& other);
    //assignment operator
    Airlift& operator = (const Airlift& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Airlift& airlift);

    //validate method to make the order valid
    void validate();
    //execute method to execute an order
    void execute() override;

    //getters and setters
    int* getNumArmies();
    void setNumArmies(int* number);
    Territory* getSource();
    void setSource(Territory* sourceTerr);
    Territory* getTarget();
    void setTarget(Territory* targetTerr);
    Player* getPlayer();
    void setPlayer(Player* player);
};

// ------------------- NEGOTIATE ORDER -----------------------
/**
 * Negotiate: user-defined subclass and one type of Order
*/
class Negotiate : public Order
{
private:
    /* data */
    Player* player;
    Player* enemy;
public:
    //default constructor
    Negotiate();
    //destructor
    ~Negotiate();
    //defined construcotr
    Negotiate(Player* player, Player* enemy);

    //copy constructor
    Negotiate(const Negotiate& other);
    //assignment operator
    Negotiate& operator = (const Negotiate& other);
    //stream operator
    friend ostream& operator << (ostream& out, const Negotiate& negotiate);

    //validate method to make the order valid
    void validate();
    //execute method to execute an order
    void execute() override;

    //getters and setters
    Player* getPlayer();
    void setPlayer(Player* player);
    Player* getEnemy();
    void setEnemy(Player* enemy);
};

// ------------------- LIST OF ORDERS ------------------------
/**
 * OrdersList: User-defined class to create and manipulate lists of orders
*/
class OrdersList : public ILoggable, public Subject
{
private:
    /* data */
    vector<Order*>* ordersList;
public:
    //default constructor
    OrdersList();
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
    //method to remove an order from the list
    void remove(Order* order);
    //method to move an order from the list
    void move(Order* order, int newPosition);

    //getter
    vector<Order*> getList();
    //setter
    void setList(vector<Order*> list);

    string stringToLog() override;
};

#endif //ORDERS_H
