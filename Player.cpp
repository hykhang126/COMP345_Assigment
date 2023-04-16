#include "Player.h"
using namespace std;

Player::Player() {
    this->name = new string("Default Player");
    this->hand = new Hand();
    this->tCollection = new vector<Territory*> {};
    this->listOfOrders = new OrdersList();
    this->reinforcement = new int(0);
    this->negotiating = new vector<Player*> {};
    this->hasConquered = new bool(false);
    this->territoriesToAttack = new vector<Territory*>();
    this->territoriesToDefend = new vector<Territory*>();
    this->gamePlayers = new vector<Player*> {};
}

Player::Player(string* name, vector<Territory*> *tCollection, Hand* hand, OrdersList* listOfOrders) {
    this->name = name;
    this->hand = hand;
    this->tCollection = tCollection;
    this->listOfOrders = listOfOrders;
    this->reinforcement = new int(0);
    this->negotiating = new vector<Player*> {};
    this->hasConquered = new bool(false);
    this->territoriesToAttack = new vector<Territory*>();
    this->territoriesToDefend = new vector<Territory*>();
    this->gamePlayers = new vector<Player*> {};
    // default constructor with no ps parameter uses human player
//    this->playerStrategy = new Human();
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
    this->negotiating = new vector<Player*>(*(p.negotiating));
    this->hasConquered = new bool(*(p.hasConquered));
    this->gamePlayers = new vector<Player*>(*(p.gamePlayers));
}

Player::~Player() {
    delete(name);
    delete(hand);
    for(auto territory : *tCollection){
        delete(territory);
    }
    delete(listOfOrders);
    delete(negotiating);
    delete(gamePlayers);
}

vector<Territory*>* Player::toDefend() {
//    return this->territoriesToDefend;
    return this->playerStrategy->toDefend();
}

vector<Territory*>* Player::toAttack() {
//    return this->territoriesToAttack;
    return this->playerStrategy->toAttack();
}

void Player::issueOrder() {
    this->playerStrategy->issueOrder();
}

bool Player::hasCardInHand(string cardName) {
    vector<Card*> cards = hand->getCardsInHand();
    for(Card* c: cards){
        if(c->getType() == cardName){
            return true;
        }
    }
    return false;
}

void Player::removeTerritory(string territoryName) {
    int i = 0;
    while(i < tCollection->size()) {
        if(*(*tCollection)[i]->getName() == territoryName) {
            tCollection->erase(tCollection->begin() + i);
        } else {
            i++;
        }
    }  
}

void Player::setTerritoriesToAttack(){
    cout << "The following territories are neighbours to the territories you own: \n";
    vector<Territory*> neighbours;
    for(Territory* t : *tCollection) {
        for(Territory* adjacentTerritory : *(t->adjacentTerritory)) {
            if(adjacentTerritory->getOwner() != this){
                neighbours.push_back(adjacentTerritory);
            }
        }    
    }
    //print out list of neighbouring territories 
    for(Territory* territory : neighbours) {
        cout << *territory->getName() << endl;
    }
    //Prompt player for priority territories
    cout << "\nPlease enter the names of the territories to be attacked in priority (separated by spaces): \n";
    string ters;
    cin.ignore();
    getline(cin, ters);
    istringstream iss(ters);
    vector<string> priorityTerritories{istream_iterator<string>{iss}, istream_iterator<string>{}};
   
    //Add territories to territories to attack
    territoriesToAttack->clear();
    for(Territory* t: neighbours) {
        for(string& pt : priorityTerritories) {        
            string territoryName = t->getName()->substr(1);
            if(*t->getName() == pt || territoryName == pt){
                territoriesToAttack->push_back(new Territory(*t));
                break;
            }
        }
    }
    cout<< "These are the territories you chose: " << endl;
    for(Territory* t: *this->territoriesToAttack){
        cout << *t->getName() << endl;
    }
}

void Player::setTerritoriesToDefend(){
    //Show territories
    cout << "\nThe following territories belong to you: \n";
    for(Territory* territory : *tCollection) {
        cout << *territory->getName() << endl;
    }
    //Prompt player for priority territories
    cout << "\nPlease enter the names of the territories to be defended in priority (separated by spaces): \n";
    string ters;
    getline(cin, ters);
    istringstream iss(ters);
    vector<string> priorityTerritories{istream_iterator<string>{iss}, istream_iterator<string>{}};
    
    //Add territories to territories to defend
    territoriesToDefend->clear();
    for(Territory* t: *tCollection) {
        bool isPriority = false;
        for(string& pt: priorityTerritories) {
            if(*t->getName() == pt) {
                isPriority = true;
                break;
            }
        }
        if(isPriority) {
            territoriesToDefend->push_back(new Territory(*t));
        }
    }
    cout<< "These are the territories you chose: " << endl;
    for(Territory* t: *this->territoriesToDefend){
        cout << *t->getName() << endl;
    }
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

vector<Player*>* Player::getNegotiating() {
    return this->negotiating;
}

void Player::setTerritoryCollection(vector <Territory*>* collection) {
    tCollection = collection;
}

void Player::addTerritory(Territory* t) {
    tCollection->push_back(t);
}

int* Player::getReinforcement() {
    return this->reinforcement;
}
void Player::setReinforcement(int* number) {
    reinforcement = number;
}
void Player::setName(string name) {
    *(this->name) = name;
}
void Player::setNegotiating(vector<Player*>* list) {
    this->negotiating = list;
}

bool* Player::getHasConquered() {
    return hasConquered;
}
void Player::setHasConquered(bool* check) {
    hasConquered = check;
}

bool* Player::getWasAttacked() {
    return this->wasAttacked;
}

PlayerStrategy* Player::getStrategy() {
    return this->playerStrategy;
}

void Player::setWasAttacked() {
    *this->wasAttacked = true;
}

Player::Player(string *name, vector<Territory *> tCollection, Hand *hand, OrdersList *listOfOrders,
               PlayerStrategy *playerStrategy) {
    this->name = new string(*name);
    this->hand = new Hand(*hand);
    this->tCollection = new vector<Territory*>;
    for(auto territory : tCollection) {
        this->tCollection->push_back(territory);
    }
    this->listOfOrders = new OrdersList(*listOfOrders);
    this->reinforcement = new int(0);
    this->negotiating = new vector<Player*> {};
    this->hasConquered = new bool(false);
    this->territoriesToAttack = new vector<Territory*>();
    this->territoriesToDefend = new vector<Territory*>();
    this->playerStrategy = playerStrategy;
}

void Player::setStrategy(PlayerStrategy *playerStrategy) {
    this->playerStrategy = playerStrategy;
}

vector<Player*>* Player::getPlayers() {
    return this->gamePlayers;
}

void Player::setPlayers(vector<Player*>* players) {
    this->gamePlayers = players;
}