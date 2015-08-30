#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game {
public:

    Game() : board() {
        round = 0;
        boardChanged = false;
        gameOver = false;
    }

    void beginGame();
    bool isGameOver();
    void endRound();

    bool play(Board::Status who, int x, int y) {
        return board.play(who, x, y);
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
