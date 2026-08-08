#ifndef GAME_HPP
#define GAME_HPP
#include "Deck.hpp"
#include "Player.hpp"
#include "Card.hpp"

using namespace std;

class Game {
public:
    //constructors
    Game(); //default

    void setUp(); //set up a new game
    void dealHands(); //deals each player their 7 card hand
    void gameState(); //display game information (your cards and how many cards bots have)

    void currentTurn(); //run the current turn 
    void nextTurn(); //goes to next player

    void actionCardEffect(Card playedCard); //checks for action card and does what the card wants
    bool checkWin(); //check if anyone has won (0 cards)
    void playGame(); //start game (main loop)

private:
    //member variables
    Deck deck; //create object
    Player players[4]; 
    Card discardPile[100]; //store cards as their played
    int discardTop;
    int currentPlayer; //remember whose turn it is
    bool clockwise; //for the reverse action card 


};
#endif