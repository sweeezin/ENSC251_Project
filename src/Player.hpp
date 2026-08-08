#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Card.hpp"

class Player {
private:
    std::string name;
    Card* hand;
    size_t handSize;
    size_t capacity;
    bool botStatus;

    // helper function to resize hand array dynamically
    void resize(size_t newCapacity);

public:
    // constructors & destructor
    Player();
    Player(const std::string& playerName, bool isBot);
    ~Player();

    // copy constructor & assignment operator for deep copying
    Player(const Player& other);
    Player& operator=(const Player& other);

    // getters
    std::string getName() const;
    bool isBot() const;
    size_t getHandSize() const;
    const Card* getHand() const;

    // hand actions
    void drawCard(const Card& card);
    Card playCard(size_t index);

    // rule verification & winning states
    bool hasValidMove(const Card& topDiscard) const;
    bool hasWon() const;

    // output methods
    void displayHand() const;
    void displayBotCardCount() const;
};

#endif // PLAYER_HPP