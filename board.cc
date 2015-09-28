#include <iostream>
#include <climits>
#include "board.h"

void Board::setup(char *state) {
}

void Board::findOpenSquaresAround(int x, int y, Board::Callback f) {
    ifOpenSquare(x-1, y-1, f);
    ifOpenSquare(x-1, y,   f);
    ifOpenSquare(x-1, y+1, f);

    ifOpenSquare(x,   y-1, f);
    ifOpenSquare(x,   y+1, f);

    ifOpenSquare(x+1, y-1, f);
    ifOpenSquare(x+1, y,   f);
    ifOpenSquare(x+1, y+1, f);
}

bool Board::play(Board::Player who, int x, int y) {
    auto square = squareId(x, y);

    if ((0 <= y && y <= 7 && 0 <= x && x <= 7) &&
        (0 == (taken & square)))
    {
        auto toBlack = who == BlackPlayer;
        auto changedBlack = black;

        changedBlack = flip(taken, changedBlack, toBlack, x, y, -1, -1);
        changedBlack = flip(taken, changedBlack, toBlack, x, y, -1,  0);
        changedBlack = flip(taken, changedBlack, toBlack, x, y, -1,  1);

        changedBlack = flip(taken, changedBlack, toBlack, x, y,  0, -1);
        changedBlack = flip(taken, changedBlack, toBlack, x, y,  0,  1);

        changedBlack = flip(taken, changedBlack, toBlack, x, y,  1, -1);
        changedBlack = flip(taken, changedBlack, toBlack, x, y,  1,  0);
        changedBlack = flip(taken, changedBlack, toBlack, x, y,  1,  1);

        if (changedBlack != black) {
            black = changedBlack;
            if (toBlack) {
                takeByBlack(square);
            }
            else {
                takeByWhite(square);
            }
            return true;
        }
    }

    return false;
}

Board::Grid Board::flip(Board::Grid taken, Board::Grid black, bool toBlack,
                        int x, int y, int dx, int dy)
{
    auto rollback = black;

    for (;;) {
        x += dx;
        y += dy;

        if (0 <= y && y <= 7 && 0 <= x && x <= 7) {
            auto square = squareId(x, y);
            if (taken & square) {
                if (black & square) {
                    if (toBlack) {
                        return black;
                    }
                    else {
                        black &= ~square;
                        continue;
                    }
                }
                else {
                    if (toBlack) {
                        black |= square;
                        continue;
                    }
                    else {
                        return black;
                    }
                }
            }
        }

        return rollback;
    }
}

void Board::print() {
    std::cout << "  abcdefgh\n";
    for (int y = 0; y <= 7; ++y) {
        std::cout << (char)('1' + y) << ' ';
        for (int x = 0; x <= 7; ++x) {
            switch (square(x, y)) {
            case OpenSquare:
                std::cout << ' ';
                break;
            case BlackSquare:
                std::cout << '#';
                break;
            case WhiteSquare:
                std::cout << 'o';
                break;
            }
        }
        std::cout << '\n';
    }
}

Board &Board::setup(int x, int y, Board::SquareStatus status) {
    auto square = squareId(x, y);
    switch (status) {
    case OpenSquare:
        clear(square);
        break;
    case BlackSquare:
        takeByBlack(square);
        break;
    case WhiteSquare:
        takeByWhite(square);
        break;
    }
    return *this;
}

Board::Grid Board::reverseBits(Board::Grid v) {
    // http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
    auto r = v;
    auto s = sizeof(v) * CHAR_BIT - 1;
    for (v >>= 1; v; v >>= 1) {
        r <<= 1;
        r |= v & 1;
        s--;
    }
    r <<= s;
    return r;
}
