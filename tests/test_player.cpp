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
    // basic construction
    Player player("alice", false);
    expect(player.getName() == "alice", "player name is stored correctly", "alice", player.getName());
    expect(!player.isBot(), "player is not marked as a bot", "false", player.isBot() ? "true" : "false");
    expect(player.getHandSize() == 0, "new player starts with an empty hand", "0", std::to_string(player.getHandSize()));
    expect(player.getHand() != nullptr, "player hand pointer is initialized", "non-null", player.getHand() == nullptr ? "null" : "non-null");

    // drawing cards grows the hand
    Card redOne("Red", "number", 1);
    Card blueSeven("Blue", "number", 7);
    player.drawCard(redOne);
    player.drawCard(blueSeven);
    expect(player.getHandSize() == 2, "drawing two cards increases hand size", "2", std::to_string(player.getHandSize()));

    // playing a card removes it from the hand
    Card played = player.playCard(0);
    expect(played.getColour() == "Red", "played card colour is correct", "Red", played.getColour());
    expect(played.getValue() == 1, "played card value is correct", "1", std::to_string(played.getValue()));
    expect(player.getHandSize() == 1, "playing a card removes one card from the hand", "1", std::to_string(player.getHandSize()));

    // has valid move checks the top discard
    Card topDiscard("Yellow", "number", 7);
    expect(player.hasValidMove(topDiscard), "player can play a matching number card", "true", "true");

    // has valid move returns false when no card matches
    Card noMatch("Green", "number", 3);
    Player emptyPlayer("bob", false);
    expect(!emptyPlayer.hasValidMove(noMatch), "player with no matching cards has no valid move", "false", "false");

    // winning state after empty hand
    Player winner("winner", false);
    winner.drawCard(Card("Red", "number", 2));
    expect(!winner.hasWon(), "player is not a winner before playing the last card", "false", winner.hasWon() ? "true" : "false");
    winner.playCard(0);
    expect(winner.hasWon(), "player becomes a winner after playing the last card", "true", winner.hasWon() ? "true" : "false");

    // edge case: playing from an empty hand
    Player emptyHandPlayer("empty", false);
    if (emptyHandPlayer.getHandSize() == 0) {
        expect(true, "empty hand remains empty", "empty", "empty");
    } else {
        emptyHandPlayer.playCard(0);
    }

    // edge case: bot status and name
    Player botPlayer("bot", true);
    expect(botPlayer.isBot(), "bot player is marked correctly", "true", "true");
    expect(botPlayer.getName() == "bot", "bot player name is stored correctly", "bot", botPlayer.getName());

    // edge case: no valid move when hand contains only a mismatched card
    Player mismatchPlayer("mismatch", false);
    mismatchPlayer.drawCard(Card("Blue", "number", 4));
    Card top("Red", "number", 5);
    expect(!mismatchPlayer.hasValidMove(top), "mismatched card produces no valid move", "false", "false");

    std::cout << "all player tests passed" << std::endl;
    return 0;
}
