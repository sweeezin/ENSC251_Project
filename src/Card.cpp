

#include "Card.hpp"
#include <iostream>
using namespace std;

Card::Card()
    : type("number"), colour("Red"), value(0)
{
}

//the constructor, which creates a card object using the colour,type and value given. Initializer list assigns each private member variable it's parameter
Card::Card(const string& colour, const string& type, int value)
    : type(type), colour(colour), value(value)
{
    if (this->type == "Number" || this->type == "NUMBER") {
        this->type = "number";
    }

//number cards use a value from 0-9
//action cards (ie: skip, reverse,draw 2) do not use a numerical value, therefore stored as -1.
    if (this->type != "number")
    {
        this->value = -1;
    }
}

//returns the card's type (ie: number, skip, reverse, draw 2)
string Card::getType() const
{
    return type;
}
//returns card's colour. (ie: red, blue, yellow, green)
string Card::getColour() const
{
    return colour;
}
//returns the card's value. Number cards return from 0-9, action cards return -1.
int Card::getValue() const
{
    return value;
}

//determines whether or not a card can actually be played on top of top card. It can only be played under the conditons that:
// 1. it's colour is the same as topCard
// 2. both cards are number cards and have the same numerical value
// 3. both cards have the same action.
bool Card::canPlayOn(const Card& topCard) const
{
// matching colour will always return as true
    if (colour == topCard.getColour())
    {
        return true;
    }
// compares the values of both cards, if they are number cards
    if (type == "number" && topCard.getType() == "number")
    {
        if (value == topCard.getValue())
        {
            return true;
        }
    }
// will return true if both cards are action card and contain the same action (ie: two skip cards)
    if (type != "number" && type == topCard.getType())
    {
        return true;
    }
//returns false is no matching conditions are met
    return false;
}

//displays the information of the card; (ie: 8 blue or red skip)
void Card::printCard() const
{
//number cards display value followed by colour
    if (type == "number")
    {
        cout << value << " " << colour;
    }
    else
    {
// action cards displace colour followed by type.
        cout << colour << " " << type;
    }
}

