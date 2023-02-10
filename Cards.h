#ifndef CARDS_H
#define CARDS_H
#include <string>
#include <vector>
using namespace std;
#include "Orders.h";

// possible card types as a global string array of pointers
string *globalCardTypes[5] = {new string("bomb"), new string("reinforcement"), new string("blockade"),new string("airlift"),new string("diplomacy")};

class Deck;

class Card
{
    private:

    string *typePter;
        Deck *deckPter;

    public:
        Card(string, Deck);
        ~Card();
        Card(const Card& c);
        Card& operator =(const Card& c);
        friend ostream& operator<<(ostream& out, const Card& card);
        string getType();
        Deck getDeck();
        void setDeck(Deck deck);
        void setType(string type);
        void play();
};

class Deck
{
    private:
        vector<Card*> *cardsInDeck;

    public:
        Deck(int);
        ~Deck();
        Deck(const Deck&);
        Deck& operator =(const Deck&);
        friend ostream& operator<<(ostream& out, const Deck& deck);
        vector<Card *> getCardsInDeck();
        void setCardsInDeck(vector <Card*>);
        void draw();
};

class Hand
{
    private:
        vector<Card*> *cardsInHand;
    
    public:
        Hand();
        ~Hand();
        Hand(const Hand& hand);
        Hand& operator =(const Hand&);
        friend ostream& operator<<(ostream& out, const Hand& hand);
        vector<Card *> getCardsInHand();
        void setCardsInHand(vector <Card*>);
        Card * removeCard();
        void addCard(Card *cardPter);

};

#endif