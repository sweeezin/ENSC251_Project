linux run
make
make run
make clean

test_player
g++ -std=c++17 -I src tests/test_player.cpp src/Card.cpp src/Player.cpp -o tests/test_player
./tests/test_player
