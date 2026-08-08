#include <iostream>
#include <string>
#include "Game.hpp"

int main() {
    std::string playerName;
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);

    if (playerName.empty()) {
        playerName = "Player 1";
    }

    Game game;
    game.setUp(playerName);
    game.playGame();
    return 0;
}
