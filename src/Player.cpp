#include "Player.hpp"
#include <iostream>

// helper function to resize hand array dynamically
void Player::resize(size_t newCapacity) {
    Card* newHand = new Card[newCapacity];
    for (size_t i = 0; i < handSize; ++i) {
        newHand[i] = hand[i];
    }
    delete[] hand;
    hand = newHand;
    capacity = newCapacity;
}

// constructors & destructor
Player::Player()
    : name("Player"), handSize(0), capacity(10), botStatus(false) {
    hand = new Card[capacity];
}

Player::Player(const std::string& playerName, bool isBot)
    : name(playerName), handSize(0), capacity(10), botStatus(isBot) {
    hand = new Card[capacity];
}

Player::~Player() {
    delete[] hand;
}

// copy constructor
Player::Player(const Player& other)
    : name(other.name), handSize(other.handSize), capacity(other.capacity), botStatus(other.botStatus) {
    hand = new Card[capacity];
    for (size_t i = 0; i < handSize; ++i) {
        hand[i] = other.hand[i];
    }
}

// assignment operator
Player& Player::operator=(const Player& other) {
    if (this != &other) {
        delete[] hand;
        name = other.name;
        handSize = other.handSize;
        capacity = other.capacity;
        botStatus = other.botStatus;
        hand = new Card[capacity];
        for (size_t i = 0; i < handSize; ++i) {
            hand[i] = other.hand[i];
        }
    }
    return *this;
}

// getters
std::string Player::getName() const {
    return name;
}

bool Player::isBot() const {
    return botStatus;
}

size_t Player::getHandSize() const {
    return handSize;
}

const Card* Player::getHand() const {
    return hand;
}

// hand actions
void Player::drawCard(const Card& card) {
    if (handSize >= capacity) {
        resize(capacity * 2);
    }
    hand[handSize] = card;
    handSize++;
}

Card Player::playCard(size_t index) {
    Card playedCard = hand[index];
    for (size_t i = index; i < handSize - 1; ++i) {
        hand[i] = hand[i + 1];
    }
    handSize--;
    return playedCard;
}

// rule verification & winning states
bool Player::hasValidMove(const Card& topDiscard) const {
    for (size_t i = 0; i < handSize; ++i) {
        if (hand[i].canPlayOn(topDiscard)) {
            return true;
        }
    }
    return false;
}

bool Player::hasWon() const {
    return handSize == 0;
}

// output methods
void Player::displayHand() const {
    std::cout << name << "'s hand:\n";
    for (size_t i = 0; i < handSize; ++i) {
        std::cout << "  [" << i << "] ";
        hand[i].printCard();
    }
}

void Player::displayBotCardCount() const {
    std::cout << name << " has " << handSize << " card(s) remaining.\n";
}