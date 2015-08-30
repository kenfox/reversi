#include <iostream>
#include "board.h"

auto main() -> int {
    bool boardChanged;
    Board b;
    b.print();

    do {
        boardChanged = false;

        if (b.playNextMove(Board::Black)) {
            b.print();
            boardChanged = true;
        }
        else {
            std::cout << "Black can't move\n";
        }

        if (b.playNextMove(Board::White)) {
            b.print();
            boardChanged = true;
        }
        else {
            std::cout << "White can't move\n";
        }
    }
    while (boardChanged);

    std::cout << "Game over\n";
    return 0;
}
