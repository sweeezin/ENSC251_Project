#include <iostream>
#include <vector>
#include "Deck.hpp"

using namespace std;

int main() {
    cout << "=== Deck Class Testing ===" << endl;

    // Test 1: Create a deck
    Deck deck;
    cout << "\nTest 1: Create deck" << endl;
    cout << "Deck size: " << deck.size() << endl;

    // Test 2: Check if new deck is empty
    cout << "\nTest 2: Check if deck is empty" << endl;
    if (deck.isEmpty())
        cout << "Deck is empty." << endl;
    else
        cout << "Deck is not empty." << endl;

    // Test 3: Draw one card
    cout << "\nTest 3: Draw one card" << endl;
    Card card = deck.drawCard();
    cout << "Card drawn: ";
    card.printCard();
    cout << endl;
    cout << "Deck size after drawing: " << deck.size() << endl;

    // Test 4: Draw five more cards
    cout << "\nTest 4: Draw 5 more cards" << endl;
    for (int i = 0; i < 5; i++) {
        Card drawnCard = deck.drawCard();
        cout << "Card " << i + 1 << ": ";
        drawnCard.printCard();
        cout << endl;
    }
    cout << "Deck size: " << deck.size() << endl;

    // Test 5: Add cards back to deck
    cout << "\nTest 5: Add cards back" << endl;
    vector<Card> cardsToAdd;
    cardsToAdd.push_back(Card("Red", "number", 5));
    cardsToAdd.push_back(Card("Blue", "Skip", -1));

    int oldSize = deck.size();
    deck.addCards(cardsToAdd);

    cout << "Old deck size: " << oldSize << endl;
    cout << "New deck size: " << deck.size() << endl;

    // Test 6: Empty deck regeneration
    cout << "\nTest 6: Empty deck regeneration" << endl;
    while (!deck.isEmpty()) {
        deck.drawCard();
    }

    cout << "Deck is empty: "
         << (deck.isEmpty() ? "Yes" : "No") << endl;

    deck.drawCard();

    cout << "Deck size after drawing from empty deck: "
         << deck.size() << endl;

    cout << "\n=== Testing Complete ===" << endl;
    return 0;
}
