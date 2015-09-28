#include <iostream>
#include "game.h"

auto main(int argc, char *argv[]) -> int {
    Game g;

    for (auto arg = 0; arg < argc; ++arg) {
        if (strcmp("-b", argv[arg]) == 0) {
            g.setupBoard(argv[++arg]);
        }
        else if (strcmp("-p", argv[arg]) == 0) {
            g.setupPlayer(argv[++arg]);
        }
    }

    g.beginGame();

#ifdef FIND_NEXT_MOVE

    return g.findNextMove();

#else

    do {
        g.print();
        if (!g.playNextMove()) {
            std::cout << "No valid move\n";
        }
    }
    while (!g.isGameOver());

    std::cout << "Game over\n";
    return 0;

#endif

}
