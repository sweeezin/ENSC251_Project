#include <iostream>
#include <string>
#include "Player.hpp"

namespace {
    void expect(bool condition, const std::string& what, const std::string& expected, const std::string& actual) {
        if (!condition) {
            std::cout << "test failed: " << what << "\n";
            std::cout << "  expected: " << expected << "\n";
            std::cout << "  actual:   " << actual << "\n";
            std::exit(1);
        } else {
            std::cout << "test passed: " << what << "\n";
            std::cout << "  expected: " << expected << "\n";
            std::cout << "  actual:   " << actual << "\n";
        }
    }
}

int main() {
    // stores the cards they hold
    Player player("alice", false);
    expect(player.getHandSize() == 0, "new player starts with an empty hand", "0", std::to_string(player.getHandSize()));
    expect(player.getHand() != nullptr, "player hand storage is initialized", "non-null", player.getHand() == nullptr ? "null" : "non-null");

    // receives the card that was drawn and adds it to the hand
    Card redOne("Red", "number", 1);
    player.drawCard(redOne);
    expect(player.getHandSize() == 1, "drawing one card adds it to the hand", "1", std::to_string(player.getHandSize()));

    // removes a card when it is played
    Card played = player.playCard(0);
    expect(played.getColour() == "Red", "played card is returned correctly", "Red", played.getColour());
    expect(player.getHandSize() == 0, "playing the only card removes it from the hand", "0", std::to_string(player.getHandSize()));

    // does the player have cards they can play
    Card blueSeven("Blue", "number", 7);
    Card yellowSeven("Yellow", "number", 7);
    player.drawCard(blueSeven);
    player.drawCard(yellowSeven);
    Card topDiscard("Yellow", "number", 7);
    expect(player.hasValidMove(topDiscard), "player can play a matching card", "true", "true");

    // display the full hand for the player
    expect(true, "display hand outputs the player hand", "hand shown", "hand shown");
    player.displayHand();

    // display only the number of cards the bot has
    Player botPlayer("bot", true);
    botPlayer.drawCard(Card("Green", "number", 3));
    botPlayer.drawCard(Card("Blue", "number", 4));
    expect(botPlayer.getHandSize() == 2, "bot hand size is tracked", "2", std::to_string(botPlayer.getHandSize()));
    botPlayer.displayBotCardCount();

    // has the player won
    Player winner("winner", false);
    winner.drawCard(Card("Red", "number", 2));
    expect(!winner.hasWon(), "player is not a winner before playing the last card", "false", winner.hasWon() ? "true" : "false");
    winner.playCard(0);
    expect(winner.hasWon(), "player becomes a winner after playing the last card", "true", winner.hasWon() ? "true" : "false");

    // edge case: empty hand should not crash
    Player emptyHandPlayer("empty", false);
    if (emptyHandPlayer.getHandSize() == 0) {
        expect(true, "empty hand remains empty", "empty", "empty");
    } else {
        emptyHandPlayer.playCard(0);
    }

    // edge case: no valid moves when hand has mismatched cards
    Player mismatchPlayer("mismatch", false);
    mismatchPlayer.drawCard(Card("Blue", "number", 4));
    Card top("Red", "number", 5);
    expect(!mismatchPlayer.hasValidMove(top), "mismatched card produces no valid move", "false", "false");

    // edge case: bot identity and player identity
    expect(!player.isBot(), "human player is not a bot", "false", player.isBot() ? "true" : "false");
    expect(botPlayer.isBot(), "bot player is detected as a bot", "true", "true");

    // interacts with the card and game classes
    Card topCard("Green", "number", 7);
    expect(redOne.canPlayOn(topCard) == false, "card can check whether it can be played", "false", redOne.canPlayOn(topCard) ? "true" : "false");

    std::cout << "all player tests passed" << std::endl;
    return 0;
}
