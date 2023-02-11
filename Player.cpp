#include "Player.h"

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
    for(auto territory : *p.tCollection){
        this->tCollection->push_back(territory);
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
    vector<Territory*>* defending = new vector<Territory*>{};
    //defending = {tCollection->begin(), tCollection->begin()+3};
    int size = tCollection->size();
    for(int i=0; i<size; i++){
        defending->push_back(tCollection[i]);
    }
    // for(auto territory: *tCollection){
    //     defending->push_back(territory);
    // }
    return defending;
}

vector<Territory*>* Player::toAttack() {
    vector<Territory*>* attacking = new vector<Territory*>;
    attacking = {tCollection->begin(), tCollection->begin() + 3};
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
        out << "\t Territory: " << territory->getName() << "\n";
    }
    out << *player.listOfOrders;
    return out;
}