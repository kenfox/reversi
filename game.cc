#include <iostream>
#include "game.h"

void Game::setupBoard(char *state) {
    if (state) {
        board.setup(state);
    }
}

void Game::setupPlayer(char *player) {
    if (player) {
        activePlayer = (player && strcmp(player, "white") == 0)
            ? Board::WhitePlayer
            : Board::BlackPlayer;
    }
}

void Game::beginGame() {
    round = 1;
    turnsWithoutChange = 0;
    boardChanged = false;
    frontier.clear();
    for (int x = 0; x <= 7; ++x) {
        for (int y = 0; y <= 7; ++y) {
            if (!board.hasOpenSquare(x, y)) {
                appendFrontier(Board::Position(x, y));
            }
        }
    }
}

bool Game::isGameOver() {
    return turnsWithoutChange >= 2;
}

void Game::endTurn() {
    activePlayer = (activePlayer == Board::BlackPlayer)
        ? Board::WhitePlayer
        : Board::BlackPlayer;

    if (activePlayer == Board::BlackPlayer) ++round;

    if (boardChanged) {
        turnsWithoutChange = 0;
        boardChanged = false;
    }
    else {
        ++turnsWithoutChange;
    }
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

bool Game::playNextMove() {
    auto played = false;
    for (auto i = frontier.cbegin(); i != frontier.cend(); ++i) {
        if (board.play(activePlayer, *i)) {
            auto playedPosition = *i;
            boardChanged = true;
            frontier.erase(i);
            appendFrontier(playedPosition);
            played = true;
            break;
        }
    }
    endTurn();
    return played;
}

void Game::print() {
    std::cout << "--------------------- Round " << round
              << " Player " << playerName()
              << std::endl;
    board.print();
}

Game &Game::setup(int x, int y, Board::SquareStatus status) {
    board.setup(x, y, status);
    return *this;
}

void Game::appendFrontier(Board::Position pos) {
    board.findOpenSquaresAround(pos.first, pos.second, [&](int x, int y) {
            auto square = Board::squareId(x, y);
            if (0 == (seen & square)) {
                seen |= square;
                frontier.emplace_back(x, y);
            }
        });
}
