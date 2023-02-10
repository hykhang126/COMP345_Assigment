#include "Cards.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include "Orders.h"
using namespace std;

// ****************** CARDS *******************

// Constructor
Card::Card(string type){
    typePter = new string(type);
}

// Destructor
Card::~Card(){
    delete(typePter);
}

// Copy constructor
Card::Card(const Card& card){
    this->typePter = new string(*(card.typePter));
}


// Assignment operator
Card& Card::operator=(const Card& card){
    this->typePter = new string(*card.typePter);
    return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& outStream, const Card& card)
{
    outStream << "Card type: " + *card.typePter + "\n";
    return outStream;
}

// Getters
string Card::getType(){
    return *typePter;
}

// Setters

void Card::setType(string type) {
    *typePter = type;
}

// Specific class functions

// Note that when playing a card, we do not want to delete and remake pointers
// We just want to move the card pointer from the hand to the deck
void Card::play(Hand *hand, Orders *order, Deck *deckPter){
    // For now, fake add the card move added to order
    //    order.addOrder();
    Card * cardPlayedPter = hand->removeCard(this);
    deckPter->addToDeck(cardPlayedPter);

};

// ****************** DECKS *******************

// Constructor
Deck::Deck(int size){
    cardsInDeck = new vector<Card*> {};

    for(int i = 0; i<size; i++){
        // Getting a random type from the possible card types, rand()%5 returns 0,1.,2,3 or 4
        int cardTypeIndex = rand()%5;
        Card *cardPter = new Card(*globalCardTypes[cardTypeIndex]);
        cardsInDeck->push_back(cardPter);
    }
}

// Destructor
Deck::~Deck(){
  for (auto p : *cardsInDeck)
   {
     delete p;
     p = NULL; // taking care of dangling, in theory ->clear() below should do this for us.
   } 
   cardsInDeck->clear();
   delete(cardsInDeck); // Since cardsInDeck is a pointer to a vector, we delete it too
   cardsInDeck=NULL;
}

// Copy constructor

Deck::Deck(const Deck& deck){
    this->cardsInDeck = new vector<Card*> {};
    for (auto card : *deck.cardsInDeck)
    {
        Card *cardToDeepCopyPter = new Card(*card);

        this->cardsInDeck->push_back(cardToDeepCopyPter);
    };
}

// Assignment operator

 Deck& Deck::operator=(const Deck& deck){
     this->cardsInDeck = new vector<Card*> {};
     for (auto card : *deck.cardsInDeck)
     {
         Card *cardToDeepCopyPter = new Card(*card);
         this->cardsInDeck->push_back(cardToDeepCopyPter);
     };
     return *this;
 }

// Stream insertion operator
ostream& operator<<(ostream& outStream, const Deck& deck)
{
    outStream << "Cards in deck are: \n";
    for (auto& card : *deck.cardsInDeck)
    {
        outStream << card->getType() + "\n";
    };
    return outStream;
}

// Getters
vector<Card*> Deck::getCardsInDeck(){
    return *cardsInDeck;
}


// Setters
// In theory this shouldn't ever be used, but here by convention.
void Deck::setCardsInDeck(vector<Card *> cards) {
    *cardsInDeck = cards;
}

// Specific Class functions

// Note that when drawing a card, we don't want to delete the pointer here!
// We just want to move it from deck to hand!
void Deck::draw(Hand *hand){
    // First shuffle the cards in deck
    std::random_device randomDevice;
    auto randomEngine = std::default_random_engine {randomDevice()};
    std::shuffle(cardsInDeck->begin(), cardsInDeck->end(), randomEngine);

    // Get the pointer to the back card
    Card * cardToDrawPter = cardsInDeck->back();
    // Add it to the hand
    hand->addCard(cardToDrawPter);
    // Then remove from the deck.
    cardsInDeck->pop_back();
}

void Deck::addToDeck(Card *card){
    cardsInDeck->push_back(card);
}

// ****************** HAND *******************

// Constructor
Hand::Hand(){
    cardsInHand = new vector<Card*> {};
}

// Destructor
Hand::~Hand(){
    // First we delete the pointers
    for (auto p : *cardsInHand)
    {
        delete p;
        p = NULL; // taking care of dangling, just in case
    }
    cardsInHand->clear(); // clearing the vector.
    delete(cardsInHand); // Since cardsInHand is a pointer to a vector, we delete it too
    cardsInHand=NULL;
}

// Copy constructor
Hand::Hand(const Hand& hand){
    this->cardsInHand = new vector<Card*> {};
    for (auto card : *hand.cardsInHand)
    {
        Card *cardToDeepCopyPter = new Card(*card);
        this->cardsInHand->push_back(cardToDeepCopyPter);
    };
}

// Assignment operator
Hand& Hand::operator=(const Hand& hand){

    this->cardsInHand = new vector<Card*> {};
    for (auto card : *hand.cardsInHand)
    {
        Card *cardToDeepCopyPter = new Card(*card);
        this->cardsInHand->push_back(cardToDeepCopyPter);
    };
    return *this;
}

// Stream insertion operator
ostream& operator<<(ostream& outStream, const Hand& hand)
{
    outStream << "Cards in hand are: \n";
    for (auto& card : *hand.cardsInHand)
    {
        outStream << card->getType() + "\n";
    };
    return outStream;
}

// Getters
vector<Card*> Hand::getCardsInHand(){
    return *cardsInHand;
}

// Setters. Shouldn't ever be used but here by convention.
void Hand::setCardsInHand(vector<Card *> cards) {
    *cardsInHand = cards;
}

// Specific Class functions
// This adds the existing pointer to the hand
// The "shallow" pointer pushing is on purpose!
// We don't want to recreate new values on the heap for already existing cards!
void Hand::addCard(Card* cardPter){
    vector<Card*> *test = cardsInHand;
    if (cardsInHand == nullptr)
    {
        cardsInHand = new vector<Card *>{};
    }
    cardsInHand->push_back(cardPter);
}

// This function is not meant to delete pointers!
// It removes a card from the hand by looking for the pointer passed!
// And returns the card pointer. Which will be returned to the deck on the rest of the Card::play() function
Card* Hand::removeCard(Card *cardPtr){
    Card *cardToRemovePter = nullptr;
    auto it = cardsInHand->begin();
    while(it != cardsInHand->end()) {
        if((*it) == cardPtr) {
            cardToRemovePter = *it;
            cardsInHand->erase(it);
            break;
        } else {
            it++;
        }
    }
    return cardToRemovePter;
}