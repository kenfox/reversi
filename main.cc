#include <iostream>
#include "game.h"

auto main() -> int {
    Game g;

    g.beginGame();
    g.print();

    do {
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

        g.endRound();
    }
    while (!g.isGameOver());

    std::cout << "Game over\n";
    return 0;
}
