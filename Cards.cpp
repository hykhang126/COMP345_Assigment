#include "Cards.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

// ****************** CARDS *******************

// Constructor
Card::Card(string type, Deck deck){
    typePter = new string(type);
    deckPter = new Deck(deck);
}

// Destructor
Card::~Card(){
    delete(typePter);
    delete(typePter);
}

// Copy constructor
Card::Card(const Card& card){
    this->deckPter = new Deck(*card.deckPter);
    this->typePter = new string(*card.typePter);
}


// Assignment operator
Card& Card::operator=(const Card& card){
    this->deckPter = new Deck(*card.deckPter);
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
Deck Card::getDeck(){
    return *deckPter;
}

// Setters

void Card::setType(string type) {
    *typePter = type;
}

void Card::setDeck(Deck deck) {
    *deckPter = deck;
}

// Specific class functions

void Card::play(){

}

// ****************** DECKS *******************

// Constructor
Deck::Deck(int size){

    for(int i = 0; i<size; i++){
        // Getting a random type from the possible card types, rand()%5 returns 0,1.,2,3 or 4
        int cardTypeIndex = rand()%5;
        cardsInDeck->push_back(
            new Card(*globalCardTypes[cardTypeIndex], *this));
    }
}

// Destructor
Deck::~Deck(){
  for (auto p : *cardsInDeck)
   {
     delete p;
   } 
   cardsInDeck->clear();
}

// Copy constructor

Deck::Deck(const Deck& deck){
    for (auto card : *deck.cardsInDeck)
    {
        this->cardsInDeck->push_back(card);
    };
}

// Assignment operator

 Deck& Deck::operator=(const Deck& deck){

     for (auto card : *deck.cardsInDeck)
     {
         this->cardsInDeck->push_back(card);
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
void Deck::setCardsInDeck(vector<Card *> cards) {
    *cardsInDeck = cards
}

// Specific Class functions
void Deck::play(){
    std::random_device randomDevice;
    auto randomEngine = std::default_random_engine {randomDevice()};
    std::shuffle(cardsInDeck->begin(), cardsInDeck->end(), randomEngine);

    // hand stuff
}

// ****************** HAND *******************

// Constructor
Hand::Hand(){

}

// Destructor
Hand::~Hand(){
    for (auto p : *cardsInHand)
    {
        delete p;
    }
    cardsInHand->clear();
}

// Copy constructor
Hand::Hand(const Hand& hand){
    for (auto card : *hand.cardsInHand)
    {
        this->cardsInHand->push_back(card);
    };
}

// Assignment operator
Hand& Hand::operator=(const Hand& hand){

    for (auto card : *hand.cardsInHand)
    {
        this->cardsInHand->push_back(card);
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

// Setters
void Hand::setCardsInHand(vector<Card *> cards) {
    *cardsInHand = cards
}

// Specific Class functions
void Hand::addCard(Card* cardPter){
    cardsInHand->push_back(cardPter);
}

Card* Hand::removeCard(){
    Card *cardPterToRemove = cardsInHand->back();
    cardsInHand->pop_back();
    return cardPterToRemove;

}