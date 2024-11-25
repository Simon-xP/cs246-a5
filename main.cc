#include "Game/abstracts.h"
#include "course.h"
#include "constants.h"
#include "tile.h"
#include <iostream>
#include <algorithm>

// STILL TODO: COMMAND LINE ARGUMENTS
// --save, --load, --board

int main() {
    tcontroller tc;
    std::shared_ptr<Player> player1 = std::make_shared<Player>("me", "qwert");
    std::shared_ptr<Player> player2 = std::make_shared<Player>("me", "qwert");
    std::shared_ptr<Player> player3 = std::make_shared<Player>("me", "qwert");
    std::shared_ptr<Player> player4 = std::make_shared<Player>("me", "qwert");
    std::shared_ptr<Player> players[4] = {player1, player2, player3, player4};
    int seed = 10;
    std::mt19937 gen(seed);
    std::shared_ptr<Board> b = generateBoard("main", players, &gen);
    // firstTurn(b.get(), &tc);
    while (std::all_of(b->data, b->data+3, [](std::shared_ptr<PlayerData> x){return x->points < 10;})) {
        run_turn(b.get(), &tc);
    }
    for (auto i : b->data) {
        if (i->points >= 10) {
            std::cout << "WINNER: " << b->players[std::distance(b->data, std::find(b->data, b->data + 3, i))]->Name << std::endl;
        }
    }
    return 0;
}