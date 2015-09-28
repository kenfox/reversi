#ifndef GAME_H
#define GAME_H

#include <utility>
#include <vector>
#include "board.h"

class Game {
public:
    Game() : board(), frontier(), seen() {
        activePlayer = Board::BlackPlayer;
        round = 0;
        turnsWithoutChange = 0;
        boardChanged = false;
    }

    void setupBoard(char *state);
    void setupPlayer(char *player);

    void beginGame();
    bool isGameOver();
    void endTurn();

    bool playNextMove();

    void print();
    Game &setup(int x, int y, Board::SquareStatus status);
    Board::SquareStatus square(int x, int y) {
        return board.square(x, y);
    }

    Board::Player player() { return activePlayer; }
    const char *playerName() { return (activePlayer == Board::BlackPlayer) ? "Black" : "White"; }

private:

    void appendFrontier(Board::Position pos);

    Board board;
    std::vector<Board::Position> frontier;
    Board::Grid seen;

    Board::Player activePlayer;
    int round;
    int turnsWithoutChange;
    bool boardChanged;
};

#endif
