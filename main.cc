#include "Game/abstracts.h"

int main() {
    Player* player1 = new Player{"me", "qwert"};
    Player* player2 = new Player{"me4", "qwert"};
    Player* player3 = new Player{"me3", "qwert"};
    Player* player4 = new Player{"me2", "qwert"};
    Player* players[4] = {player1, player2, player3, player4};
    int seed;
    std::mt19937 gen(seed);
    Board* b = generateBoard("main", players, &gen);
    while (true) {
        run_turn(b);
    }
}