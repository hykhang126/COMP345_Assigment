#include "Player.h"
using namespace std;

Player::Player() {
    this->name = new string("Default Player");
    this->hand = new Hand();
    this->tCollection = new vector<Territory*> {};
    this->listOfOrders = new OrdersList();
}

Player::Player(string* name, vector<Territory*> tCollection, Hand* hand, OrdersList* listOfOrders) {
    this->name = new string(*name);
    this->hand = new Hand(*hand);
    this->tCollection = new vector<Territory*>;
    for(auto territory : tCollection) {
        this->tCollection->push_back(territory);
    }
    this->listOfOrders = new OrdersList(*listOfOrders);
}

Player::Player(const Player& p) {
    this->name = new string(*p.name);
    this->hand = new Hand(*p.hand);
    this->tCollection = new vector<Territory*>;
    for(auto territory : *p.tCollection){
        Territory* territoryCopy = new Territory(*territory);
        this->tCollection->push_back(territoryCopy);
    }
    this->listOfOrders = new OrdersList(*p.listOfOrders);
}

Player::~Player() {
    delete(name);
    delete(hand);
    for(auto territory : *tCollection){
        delete(territory);
    }
    delete(listOfOrders);
}

vector<Territory*>* Player::toDefend() {
    //creating player for territory objects
    //creating other attributes necessary to create territories
    int armies1 = 5, armies2 = 10, armies3 = 15;
    int pos1 = 1, pos2 = 2, pos3 = 3;
    string *name1 = new string("D Territory1"), *name2 = new string("D Territory2"), *name3 = new string("D Territory3");
    //Creating continents for territories
    string contName1 = "Continent1", contName2 = "Continent2", contName3 = "Continent3";
    string color1 = "Red", color2 = "Blue", color3 = "Green";
    int point1 = 1, point2 = 2, point3 = 3;
    Continent* continent1 = new Continent(&pos1, &contName1, &point1, &color1); 
    Continent* continent2 = new Continent(&pos2, &contName2, &point2, &color2);
    Continent* continent3 = new Continent(&pos3, &contName3, &point3, &color3);
    //Creating coordinate objects for territoreis
    int x = 1, y = 2;
    Coordinate* coordinate1 = new Coordinate(&x, &y);
    Coordinate* coordinate2 = new Coordinate(&x, &y);
    Coordinate* coordinate3 = new Coordinate(&x, &y);
    //Creating arbitrary Territories
    Territory* territory1 = new Territory(this, &armies1, &pos1, name1, continent1, coordinate1);
    Territory* territory2 = new Territory(this, &armies2, &pos2, name2, continent2, coordinate2);
    Territory* territory3 = new Territory(this, &armies3, &pos3, name3, continent3, coordinate3);
    //Creating list of arbitraty territories
    vector<Territory*>* defending = new vector<Territory*>{territory1, territory2, territory3};
    return defending;
}

vector<Territory*>* Player::toAttack() {
    //creating players for territory objects
    //creating other attributes necessary to create territories
    int armies1 = 5, armies2 = 10, armies3 = 15;
    int pos1 = 1, pos2 = 2, pos3 = 3;
    string *name1 = new string("A Territory1"), *name2 = new string("A Territory2"), *name3 = new string("A Territory3");
    //Creating continents for territories
    string contName1 = "Continent1", contName2 = "Continent2", contName3 = "Continent3";
    string color1 = "Red", color2 = "Blue", color3 = "Green";
    int point1 = 1, point2 = 2, point3 = 3;
    Continent* continent1 = new Continent(&pos1, &contName1, &point1, &color1); 
    Continent* continent2 = new Continent(&pos2, &contName2, &point2, &color2);
    Continent* continent3 = new Continent(&pos3, &contName3, &point3, &color3);
    //Creating coordinate objects for territoreis
    int x = 1, y = 2;
    Coordinate* coordinate1 = new Coordinate(&x, &y);
    Coordinate* coordinate2 = new Coordinate(&x, &y);
    Coordinate* coordinate3 = new Coordinate(&x, &y);
    //Creating arbitrary Territories
    Territory* territory1 = new Territory(this, &armies1, &pos1, name1, continent1, coordinate1);
    Territory* territory2 = new Territory(this, &armies2, &pos2, name2, continent2, coordinate2);
    Territory* territory3 = new Territory(this, &armies3, &pos3, name3, continent3, coordinate3);
    //Creating list of arbitraty territories
    vector<Territory*>* attacking = new vector<Territory*>{territory1, territory2, territory3};
    return attacking;
}

void Player::issueOrder() {
    Order *ord = new Order();
    this->listOfOrders->addOrder(ord);
}

Player& Player::operator=(const Player& p) {
    this->name = new string(*p.name);
    this->hand = new Hand(*p.hand);
    this->tCollection = new vector<Territory*>;
    for(auto territory : *p.tCollection) {
        this->tCollection->push_back(territory);
    }
    this->listOfOrders = new OrdersList(*p.listOfOrders);
    return *this;
}

ostream& operator<<(ostream& out, const Player& player) {
    out << "Player: " + *player.name + "\n";
    out << *player.hand;
    out << "Collection: \n";
    for (const auto& territory : *player.tCollection) {
        out << "\t Territory: " << *territory->getName() << "\n";
    }
    out << *player.listOfOrders;
    return out;
}

string* Player::getName() {
    return this->name;
}

Hand* Player::getHand() {
    return this->hand;
}

OrdersList* Player::getOrdersList() {
    return this->listOfOrders;
}

vector<Territory*>* Player::getTerritoryCollection() {
    return this->tCollection;
}

void Player::setTerritoryCollection(vector <Territory*> collection) {
    *tCollection = collection;
}
