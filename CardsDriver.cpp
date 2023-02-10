
#include <iostream>
#include <vector>
#include "Cards.h"

using namespace std;
int main() {


    // Making a first deck
    Deck *firstDeck = new Deck(15);

    cout << "****Printing First Deck below****\n" << *firstDeck;

    // Making an empty hand
    Hand *hand = new Hand();

    // Testing Copy Constructor
    Deck *secondDeck = new Deck(*firstDeck);
    // At this stage, the first and second deck should have the same values

    cout<< "****Printing Second Deck below****\n" << *secondDeck;

    // Drawing 10 cards from the second deck and testing assignment operator
    Deck thirdDeck = *secondDeck;
    for (int i = 0; i < 10; i ++){
        secondDeck->draw(hand);
    }

    // Now we can see that second deck and first deck have a different number of cards.
    cout<< "****Filled first deck below****\n" << *firstDeck;
    cout << "****Short second deck below****\n" << *secondDeck << "\n ****Deep copy successful above****\n";
    // Also, the third deck (assignment operator) has a different number of cards than the second deck
    cout<<"****Deep assignment below:**** \n" << thirdDeck;

    // Next we make sure that the hand is filled
    cout << "****Printing Hand****\n" << *hand << "****Hand successfully filled above****\n";
    // We can also print a new card
    cout << *(new Card("Test Card"));
    // Making an orderlist before we can play cards
    Order *orderList = new Order();
    // Next we play many random cards from the back of the hand. Note that when playing a card, the cards in the hand are shuffled first.
    for (int i = 0; i < 8; i++){
        hand->getCardsInHand().back()->play(hand,orderList,secondDeck);
    }
    // Next we print the hand again to show that many of the cards are gone from the hand

    cout << *hand << "\n ****We went from 10 cards to 2 above ****\n";

    cout<< "****The second deck is filled again below****\n"<<*secondDeck;



}


