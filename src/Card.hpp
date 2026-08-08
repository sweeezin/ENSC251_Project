
#ifndef CARD_HPP
#define CARD_HPP

#include <string>
using namespace std;

class Card {
private:
    string type;    // for number, draw 2, skip, or reverse
    string colour;  // for colours (red, blue, yellow, green)
    int value;      // for number on the card (0-9). remains unused for action cards

public:
    // constructor
    Card(const string& colour, const string& type, int value);

    ~Card() = default;

    // getters
    string getType() const;
    string getColour() const;
    int getValue() const;

    // checks if card can be played on top of topCard
    bool canPlayOn(const Card& topCard) const;

    // output
    void printCard() const;
};

#endif
