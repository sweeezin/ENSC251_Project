#include "Deck.hpp"

#include <algorithm>
#include <random>
#include <stdexcept>

Deck::Deck() {
    createDeck();
    shuffle();
}

void Deck::createDeck() {
    // Remove any cards that may already be in the deck.
    cards.clear();

    const std::string colours[] = {"Red", "Blue", "Green", "Yellow"};

    for (const std::string& colour : colours) {
        // Each colour has one zero card.
        cards.push_back(Card(colour, "number", 0));

        // Each colour has two copies of number cards 1 to 9.
        for (int value = 1; value <= 9; value++) {
            cards.push_back(Card(colour, "number", value));
            cards.push_back(Card(colour, "number", value));
        }

        // Each colour has two copies of every action card.
        for (int copy = 0; copy < 2; copy++) {
            cards.push_back(Card(colour, "Skip", -1));
            cards.push_back(Card(colour, "Reverse", -1));
            cards.push_back(Card(colour, "Draw2", -1));
        }
    }
}

void Deck::shuffle() {
    // Create a random number generator and use it to shuffle the vector.
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::shuffle(cards.begin(), cards.end(), generator);
}

Card Deck::drawCard() {
    if (isEmpty()) {
        createDeck();
        shuffle();
    }

    // The last card in the vector is treated as the top card.
    Card topCard = cards.back();
    cards.pop_back();

    return topCard;
}

bool Deck::isEmpty() const {
    return cards.empty();
}

int Deck::size() const {
    return static_cast<int>(cards.size());
}

void Deck::addCards(const std::vector<Card>& newCards) {
    for (const Card& card : newCards) {
        cards.push_back(card);
    }
}
