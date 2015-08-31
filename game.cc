#include <iostream>
#include "game.h"

void Game::beginGame() {
    round = 1;
    gameOver = false;
    boardChanged = false;
    for (int x = 0; x <= 7; ++x) {
        for (int y = 0; y <= 7; ++y) {
            if (!board.openSquare(x, y)) {
                appendPossibleMoves(x, y);
            }
        }
    }
}

bool Game::isGameOver() {
    return gameOver;
}

void Game::endRound() {
    ++round;
    gameOver = !boardChanged;
    boardChanged = false;
}

bool Game::play(Board::Status who, Game::Position p) {
    return board.play(who, p.first, p.second);
}

/*

playNextMove is responsible for choosing the best play for both Black
and White. It currently plays the first legal move that's found in the
list of boundary squares.  The boundary squares are enqueued when a
square is taken, so the combined effect is to make legal moves near
the center of the board.

This is really naive, but generates a realistic looking game.

Future Algorithm Thoughts

Each possible legal move should be ranked and the best move
taken. This is essentially a depth 1 lookahead. No change to
the data structures are necessary, but the board must be
restored after evaluating each play.

Heuristics such as taking edges and not giving up squares can be
incorporated into the ranking.

Extending to depth N requires copying the Game object, applying a
potential play, then fanning out the next possible moves for the other
color. Depth 5 will probably evaluate 50,000 boards and use 32MB of
memory. Depth 7 jumps to over 2 million boards and 2GB of memory.

The naive approach plays an entire game of 32 rounds in 5ms on one
core. Even adopting multi-core it seems unlikely to get past depth 5
lookahead with a brute force search.

 */

bool Game::playNextMove(Board::Status who) {
    for (auto i = possibleMove.cbegin(); i != possibleMove.cend(); ++i) {
        if (play(who, *i)) {
            auto playedPosition = *i;
            boardChanged = true;
            possibleMove.erase(i);
            appendPossibleMoves(playedPosition.first, playedPosition.second);
            return true;
        }
    }
    return false;
}

void Game::print() {
    std::cout << "--------------------- Round " << round << std::endl;
    board.print();
}

Game &Game::setup(int x, int y, Board::Status status) {
    board.setup(x, y, status);
    return *this;
}

void Game::appendPossibleMoves(int x, int y) {
    board.findOpenSquaresAround(x, y, [&](int x, int y) {
            auto mask = Board::bit(x, y);
            if (0 == (seen & mask)) {
                seen |= mask;
                possibleMove.emplace_back(x, y);
            }
        });
}
