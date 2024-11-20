#include "Game/abstracts.h"
#include "course.h"
#include "constants.h"
#include "tile.h"
#include <iostream>
#include <algorithm>

int main() {
    std::shared_ptr<Player> player1 = std::make_shared<Player>("me", "qwert");
    std::shared_ptr<Player> player2 = std::make_shared<Player>("me", "qwert");
    std::shared_ptr<Player> player3 = std::make_shared<Player>("me", "qwert");
    std::shared_ptr<Player> player4 = std::make_shared<Player>("me", "qwert");
    Player* players[4] = {player1.get(), player2.get(), player3.get(), player4.get()};
    int seed = 10;
    std::mt19937 gen(seed);
    std::shared_ptr<Board> b = generateBoard("main", players, &gen);
    firstTurn(b.get());
    while (std::all_of(b->data, b->data+3, [](std::shared_ptr<PlayerData> x){return x->points < 10;})) {
        run_turn(b.get());
    }
    for (auto i : b->data) {
        if (i->points >= 10) {
            std::cout << "WINNER: " << b->players[std::distance(b->data, std::find(b->data, b->data + 3, i))]->Name << std::endl;
        }
    }
    return 0;
}