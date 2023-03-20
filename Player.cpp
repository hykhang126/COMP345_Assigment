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
}

Player::Player(string* name, vector<Territory*> tCollection, Hand* hand, OrdersList* listOfOrders) {
    this->name = new string(*name);
    this->hand = new Hand(*hand);
    this->tCollection = new vector<Territory*>;
    for(auto territory : tCollection) {
        this->tCollection->push_back(territory);
    }
    this->listOfOrders = new OrdersList(*listOfOrders);
    this->negotiating = new vector<Player*> {};
    this->hasConquered = new bool(false);
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
}

Player::~Player() {
    delete(name);
    delete(hand);
    for(auto territory : *tCollection){
        delete(territory);
    }
    delete(listOfOrders);
    delete(negotiating);
}

vector<Territory*>* Player::toDefend() {
    return this->territoriesToDefend;
}

vector<Territory*>* Player::toAttack() {
    return this->territoriesToAttack;
}

void Player::issueOrder() {
    
    int orderOption;
    this->setTerritoriesToAttack();
    this->setTerritoriesToDefend();

    do {
        cout << "Please enter a number between 1 to 7 to select your desired order: \n 1. Negotiate \n 2. Airlift \n 3. Blockade \n 4. Bomb"
        "\n 5. Advance \n 6. Deploy \n 7. Finish" << endl;

        cin>>orderOption;

        switch (orderOption)
        {
        case 1:
            if(this->getReinforcement() != 0) {
                cout << "You must deploy all your armies before any other order" << endl;;
                break;
            } else if (this->hasCardInHand("Negotiate")){
                string playerToNegotiate;
                cout << "Enter the name of the player you would like to negotiate with " << endl;
                cin >> playerToNegotiate;
                this->listOfOrders->addOrder(new Negotiate());
                break;
            } else {
                cout << "You cannot add this order as you do not have the proper card in hand!" << endl;
            } 
            break;
        case 2:
            if(this->getReinforcement() != 0) {
                cout << "You must deploy all your armies before any other order" << endl;
                break;
            } else if (this->hasCardInHand("Airlift")){
                cout << "The following is a list of the territories you own: " << endl; 
                vector<Territory*>* ownedTerritories = this->getTerritoryCollection();
                for(auto it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it){
                    cout << (*it)->getName() << ", Armies: " << (*it)->getArmies() << endl;
                }

                string srcTerritory;
                string targetTerritory;
                int number;

                cout << "\nEnter the source territory for the airlift: " << endl;
                cin >> srcTerritory;
                cout << "Enter the target territory for the airlift: " << endl;
                cin >> targetTerritory;
                cout << "Enter the number of armies for the airlift: " << endl;
                cin >> number;

                Territory* src = nullptr;
                Territory* target = nullptr;
                for (auto& terr : *ownedTerritories) {
                    if (*terr->getName() == srcTerritory) {
                        src = terr;
                    } else if (*terr->getName() == targetTerritory) {
                        target = terr;
                    }
                }
                if (src == nullptr || target == nullptr) {
                    cout << "One of the territories entered does not exist or does not belong to the player." << endl;
                } else {
                    this->listOfOrders->addOrder(new Airlift(&number, src, target, this));
                }
            } else {
                cout << "You cannot add this order as you do not have the proper card in hand!" << endl;
            }
            break;
        case 3:
            if(this->getReinforcement() != 0) {
                cout << "You must deploy all your armies before any other order" << endl;
                break;
            } else if (this->hasCardInHand("Blockade")){
                cout << "The following is a list of the territories you own: " << endl; 
                vector<Territory*>* ownedTerritories = this->getTerritoryCollection();
                for(auto it = ownedTerritories->begin(); it != ownedTerritories->end(); ++it){
                    cout << (*it)->getName() << ", Armies: " << (*it)->getArmies() << endl;
                }

                string targetTerritory;
                cout << "Enter the target territory for the blockade: " << endl;
                cin >> targetTerritory;

                Territory* target = nullptr;
                for (auto& terr : *ownedTerritories) {
                    if (*terr->getName() == targetTerritory) {
                        target = terr;
                    }
                }
                if (target == nullptr) {
                    cout << "One of the territories entered does not exist or does not belong to the player." << endl;
                } else {
                    this->listOfOrders->addOrder(new Blockade(target, this));
                }
            } else {
                cout << "You cannot add this order as you do not have the proper card in hand!" << endl;
            }
            break;
        case 4:
            if(this->getReinforcement() != 0) {
                cout << "You must deploy all your armies before any other order" << endl;
                break;
            } else if (this->hasCardInHand("Bomb")){
                string targetTerritory;
                cout << "Enter the target territory for the bomb: " << endl;
                cin >> targetTerritory;
                this->listOfOrders->addOrder(new Bomb());
            } else {
                cout << "You cannot add this order as you do not have the proper card in hand!" << endl;
            }
            break;
        case 5:
            if(this->getReinforcement() != 0) {
                cout << "You must deploy all your armies before any other order" << endl;
                break;
            } else {
                cout << "The following territories are your list of territories to be defended along with how many armies they currently have: " << endl;
                vector<Territory*>* defendList = this->toDefend();
                for(auto it = defendList->begin(); it != defendList->end(); ++it){
                    cout << (*it)->getName() << ", Armies: " << (*it)->getArmies() << endl;
                }

                cout << "\nThe following territories are your list of terrirotires to attack:" << endl;
                vector<Territory*>* attackList = this->toAttack();
                for(auto it = attackList->begin(); it != attackList->end(); ++it){
                    cout << (*it)->getName() << endl;
                }

                string srcTerritory;
                string targetTerritory;
                int number;

                cout << "Enter the source territory for the advance: " << endl;
                cin >> srcTerritory;
                cout << "Enter the target territory for the advance: " << endl;
                cin >> targetTerritory;
                cout << "Enter the number of armies for the advance: " << endl;
                cin >> number;

                Territory* srcTerritoryPtr = nullptr;
                Territory* targetTerritoryPtr = nullptr;
                bool isDefend = false;
                bool isAttack = false;

                for (auto it = defendList->begin(); it != defendList->end(); ++it) {
                    if (*(*it)->getName() == targetTerritory) {
                        isDefend = true;
                        targetTerritoryPtr = *it;
                        break;
                    }
                }
                for (auto it = attackList->begin(); it != attackList->end(); ++it) {
                    if (*(*it)->getName() == targetTerritory) {
                        isAttack = true;
                        targetTerritoryPtr = *it;
                        break;
                    }
                }

                for (auto& terr : *tCollection) {
                        if (*terr->getName() == srcTerritory) {
                            srcTerritoryPtr = terr;
                        }
                }

                this->listOfOrders->addOrder(new Advance(&number, srcTerritoryPtr, targetTerritoryPtr, this));
            }
            break;
        case 6:
            cout << "The following territories are your list of territories to be defended along with how many armies they currently have: " << endl;
            vector<Territory*>* defendList = this->toDefend();
            for(auto it = defendList->begin(); it != defendList->end(); ++it){
                cout << (*it)->getName() << ", Armies: " << (*it)->getArmies() << endl;
            }
            cout << "You currently have " << this->getReinforcement() << " available armies to deploy." << endl;
            for(auto it = defendList->begin(); it != defendList->end(); ++it){
                int armiesToDeploy;
                cout << "How many armies would you like to deploy to " << (*it)->getName() << " ?" <<endl;
                cin >> armiesToDeploy;
                while(armiesToDeploy > *this->getReinforcement()){
                    cout << "Invalid input. You only have " << this->getReinforcement() << " armies to deploy. Please enter a valid number." << endl;
                    cin >> armiesToDeploy;
                }
                this->setReinforcement(*this->getReinforcement() - armiesToDeploy);
                this->listOfOrders->addOrder(new Deploy(&armiesToDeploy, *it, this));
            }
            break;
        case 7:
            if(this->getReinforcement() != 0) {
                cout << "You must deploy all your armies before any other order";
                break;
            }
            break;       
        }
    } while (orderOption != 7 && this->getReinforcement() !=0);
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

void Player::setTerritoriesToAttack(){
    cout << "The following territories are neighbours to the territories you own: \n";
    vector<Territory*> neighbours;
    for(Territory* t : *tCollection) {
        for(Territory* adjacentTerritory : *(t->adjacentTerritoriy)) {
            if(adjacentTerritory->getOwner() != this){
                neighbours.push_back(adjacentTerritory);
            }
        }    
    }
    //print out list of neighbouring territories 
    for(Territory* territory : neighbours) {
        cout << territory->getName() << endl;
    }
    //Prompt player for priority territories
    cout << "Please enter the names of the territories to be attacked in priority (separated by spaces): \n";
    string ters;
    getline(cin, ters);
    istringstream iss(ters);
    vector<string> priorityTerritories{istream_iterator<string>{iss}, istream_iterator<string>{}};
    //Add territories to territories to attack
    territoriesToAttack->clear();
    for(Territory* t: neighbours) {
        if(find(priorityTerritories.begin(), priorityTerritories.end(), t->getName()) != priorityTerritories.end()){
            territoriesToAttack->push_back(new Territory(*t));
        }
    }
}

void Player::setTerritoriesToDefend(){
    //Show territories
    cout << "The following territories belong to you: \n";
    for(Territory* territory : *tCollection) {
        cout << territory->getName() << endl;
    }
    //Prompt player for priority territories
    cout << "Please enter the names of the territories to be defended in priority (separated by spaces): \n";
    string ters;
    getline(cin, ters);
    istringstream iss(ters);
    vector<string> priorityTerritories{istream_iterator<string>{iss}, istream_iterator<string>{}};
    //Add territories to territories to defend
    territoriesToDefend->clear();
    for(Territory* t: *tCollection) {
        if(find(priorityTerritories.begin(), priorityTerritories.end(), t->getName()) != priorityTerritories.end()) {
            territoriesToDefend->push_back(t);
        } 
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