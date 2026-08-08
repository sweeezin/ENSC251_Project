#ifndef DECK_HPP
#define DECK_HPP

#include "Card.hpp"
#include <vector>

class Deck {
public:
    // Creates and shuffles the full 100-card deck
    Deck();

    ~Deck() = default;

    // Builds or rebuilds all number and action cards
    void createDeck();

    // Randomizes the order of the cards
    void shuffle();

    // Removes and returns the top card from the deck
    Card drawCard();

    // Returns true when no cards remain in the deck
    bool isEmpty() const;

    // Returns the number of cards currently remaining
    int size() const;

    // Adds a collection of cards back into the deck
    // This can be used when recycling the discard pile
    void addCards(const std::vector<Card>& newCards);

private:
    std::vector<Card> cards;
};

#endif // DECK_HPP
