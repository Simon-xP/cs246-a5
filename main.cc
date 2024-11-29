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
    std::shared_ptr<Player> player2 = std::make_shared<Player>("me1", "qwert");
    std::shared_ptr<Player> player3 = std::make_shared<Player>("me2", "qwert");
    std::shared_ptr<Player> player4 = std::make_shared<Player>("me3", "qwert");
    std::shared_ptr<Player> players[4] = {player1, player2, player3, player4};
    int seed = 8637;
    std::mt19937 gen(seed);
    // std::shared_ptr<Board> b = openFile("heck", "main", players, &gen);
    std::shared_ptr<Board> b = generateBoard("main", players, &gen);
    
    
    return 0;
}
