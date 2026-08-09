#include "Game.hpp"
#include <iostream>

using namespace std;

int main() {
    Game game;
    cout << "test set up" << endl;
    game.setUp("Test Player");
    cout << "Test game" << endl;
    game.playGame();

    return 0;


}