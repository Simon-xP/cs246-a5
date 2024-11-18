#include "Game/abstracts.h"
#include "course.h"
#include "constants.h"
#include "tile.h"
#include <iostream>
#include <algorithm>

int main() {
    Player* player1 = new Player{"me", "qwert"};
    Player* player2 = new Player{"me4", "qwert"};
    Player* player3 = new Player{"me3", "qwert"};
    Player* player4 = new Player{"me2", "qwert"};
    Player* players[4] = {player1, player2, player3, player4};
    int seed = 10;
    std::mt19937 gen(seed);
    Board* b = generateBoard("main", players, &gen);
    firstTurn(b);
    while (std::all_of(b->data, b->data+3, [](PlayerData* x){return x->points < 10;})) {
        run_turn(b);
    }
    for (auto i : b->data) {
        if (i->points >= 10) {
            std::cout << "WINNER: " << b->players[std::distance(b->data, std::find(b->data, b->data + 3, i))]->Name << std::endl;
        }
    }
    delete b;
}