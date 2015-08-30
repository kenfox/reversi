#ifndef GAME_H
#define GAME_H

#include <utility>
#include "board.h"

class Game {
public:
    using Position = std::pair<int, int>;

    Game() : board() {
        round = 0;
        boardChanged = false;
        gameOver = false;
    }

    void beginGame();
    bool isGameOver();
    void endRound();

    bool play(Board::Status who, Position p) {
        return board.play(who, p.first, p.second);
    }
    bool playNextMove(Board::Status who);

    void print();
    Game &setup(int x, int y, Board::Status status);
    Board::Status square(int x, int y) {
        return board.square(x, y);
    }

private:

    Board board;

    int round;
    bool boardChanged;
    bool gameOver;
};

#endif
