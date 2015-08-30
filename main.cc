#include <iostream>
#include "game.h"

auto main() -> int {
    Game g;
    g.print();

    for (g.beginGame(); !g.isGameOver(); g.endRound()) {
        if (g.playNextMove(Board::Black)) {
            g.print();
        }
        else {
            std::cout << "Black can't move\n";
        }

        if (g.playNextMove(Board::White)) {
            g.print();
        }
        else {
            std::cout << "White can't move\n";
        }
    }

    std::cout << "Game over\n";
    return 0;
}
