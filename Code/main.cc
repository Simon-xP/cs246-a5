#include "Game/abstracts.h"

int main() {
    Board* b = new Board{};
    while (true) {
        run_turn(b);
    }
}