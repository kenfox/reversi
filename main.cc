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
    g.print();

#ifdef FIND_NEXT_MOVE

    return g.findNextMove();

#else

    do {
        std::cout << g.playerName() << " to move\n";

        if (g.playNextMove()) {
            g.print();
        }
        else {
            std::cout << "no valid move\n";
        }
    }
    while (!g.isGameOver());

    std::cout << "Game over\n";
    return 0;

#endif

}
