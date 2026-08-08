#include "Game.hpp"
#include <iostream>
using namespace std;

Game::Game() { //default 
    currentPlayer = 0; //first player
    clockwise = true; //moving in clockwise
    discardTop = 0; //make pile empty
}

void Game::setUp() { //build everything
    //create Players
    players[0]= Player("Player 1", false); //human
    players[1]= Player("Bot 1", true);
    players[2]= Player("Bot 2", true); 
    players[3]= Player("Bot 3", true);
    //initilize starting values
    discardTop = 0;
    currentPlayer = 0;
    clockwise = true;
    //deal new hands
    dealHands();
    //draw a card for discard pile
    discardPile[discardTop] = deck.drawCard();
    discardTop++;
    //starting card
    cout << "Card to start: ";
    discardPile[discardTop - 1].printCard(); 
    cout << endl;


}


void Game::dealHands() {
    //loop around 7 times giving one card to each player every round
    //round 0 is when 1 card is added
    for (int i = 0; i < 7; ++i) { //loop 7 rounds
        for (int p = 0; p < 4; p++) { //through every index of players
            Card card = deck.drawCard(); //draw card
            players[p].drawCard(card); //add to players hand
        }
    }
}

void Game::currentTurn() {
    Player& player = players[currentPlayer]; //know the current player
    Card& topCard = discardPile[discardTop - 1]; //know whats on the top of the pile
    cout << "It is " << player.getName() << "'s turn. The top card is " ; //print starting info
    topCard.printCard();
    cout << endl;
    
    //human
    if(!player.isBot()) { //not a bot
        //valid card in hand
        while(!player.hasValidMove(discardPile[discardTop -1])) { 
            cout << "Can't play a valid card. Drew a card." << endl;
            player.drawCard(deck.drawCard()); //draw new card
        }

        player.displayHand(); //show what they have
        //choose card to play
        int chosenCard; //create variable
        cout << "choose a card: " << endl; //ask player to choose what card they want to play 
        cin >> chosenCard;
        Card playedCard = player.playCard(chosenCard); //play that card

        //played card validity
        while (!playedCard.canPlayOn(discardPile[discardTop - 1])) { //is the card they chose playable
            cout << "Not a valid card, choose again." << endl;
            player.drawCard(playedCard); //take it back, adds card to end of their hand
            cin >> chosenCard;
            playedCard = player.playCard(chosenCard); 
        }

        //add to pile
        discardPile[discardTop] = playedCard;
        discardTop++;
        //display played card
        playedCard.printCard();
        cout << " was played." << endl;

        actionCardEffect(playedCard); //if action card


    } else { //Bot playing
        bool played = false;
        while (!played) { //bot keeps looking for a valid card and draws if it doesnt find one
            for (size_t i = 0; i < player.getHandSize(); i++) { //look for valid card
                Card card = player.getHand()[i]; //access cards using [i]

                if(card.canPlayOn(discardPile[discardTop -1])) { //is the card playbale
                Card playedCard = player.playCard(i); //play the card if valid

                    discardPile[discardTop] = playedCard; //add card to pile
                    discardTop++;

                    playedCard.printCard(); 
                    cout << " played by " << player.getName() << endl;

                    actionCardEffect(playedCard); //action card

                    played = true;
                    break; //stop bot after it played its turn


                }
            }
            if (!played) { //no card played by bot
                cout << player.getName() << " not a playable card. Draw another card." << endl;
                player.drawCard(deck.drawCard());
            }
        }
    }

}



void Game::nextTurn() {
    if(clockwise) {
        currentPlayer ++; //move to next player
        if(currentPlayer > 3) { //if at last player (4)
            currentPlayer = 0; //go back to first player (0)
        }
    } else { //if going counter clockwise
        currentPlayer--; //go the other way
        if (currentPlayer < 0) { //go back to player 3 when player 0 is reached
            currentPlayer = 3;
        }

    }
    
}

bool Game::checkWin() { 
    for( int i =0; i < 4; i++) { //loop through players
        if (players[i].hasWon()) { //when someone has no cards in thier hand
            cout << players[i].getName() << " has won" << endl;
            return true;
        }
    }
    return false;
}

void Game::actionCardEffect(Card playedCard) {
    if (playedCard.getType() == "Reverse") {
        cout << "Reverse played. Changing direction." << endl;
        clockwise = !clockwise; //change direction

    } else if(playedCard.getType() == "Skip") {
        cout << "Skip played. Skipping turn." << endl;
        nextTurn();

    } else if(playedCard.getType() == "Draw2") {
        cout << "Drawing 2 and skipping turn." << endl;

        int nextPlayer;
        if(clockwise) { //find who is next
            nextPlayer = currentPlayer + 1; 
            if(nextPlayer > 3) { //if reached end of list
                nextPlayer = 0; //go back to player 1
            }
        } else { //counter clockwise
            nextPlayer = currentPlayer - 1; //go backwards
            if(nextPlayer < 0) { 
                nextPlayer = 3;
            }
        }

        players[nextPlayer].drawCard(deck.drawCard());
        players[nextPlayer].drawCard(deck.drawCard());
        nextTurn(); //skip turn after drawing 2
    }

}

void Game::gameState() {
    cout << "Current Game Information:" << endl;
    cout << "Current card on top: ";
    discardPile[discardTop - 1].printCard();
    cout << endl;

    //bots cards
    for (int i = 1; i < 4; i++) {
        players[i].displayBotCardCount();
    }
    cout << endl;

    //human cards
    players[0].displayHand();
    cout << endl;
}

void Game::playGame() { //run the game
    while (!checkWin()) { //check if game ended
        gameState();
        currentTurn();
        nextTurn();
    }

}
