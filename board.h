#ifndef BOARD_H
#define BOARD_H

#include <functional>

class Board {
public:
    enum Player {
        WhitePlayer, BlackPlayer
    };
    enum SquareStatus {
        WhiteSquare, BlackSquare, OpenSquare
    };

#define GRID(R1,R2,R3,R4,R5,R6,R7,R8) reverseBits(0b##R1##R2##R3##R4##R5##R6##R7##R8)

    Board() {
        taken = GRID(00000000,
                     00000000,
                     00000000,
                     00011000,
                     00011000,
                     00000000,
                     00000000,
                     00000000);
        black = GRID(00000000,
                     00000000,
                     00000000,
                     00001000,
                     00010000,
                     00000000,
                     00000000,
                     00000000);
    }

    void setup(char *state);

    // squares on the board are represented as bits in a 64-bit int
    using Grid = unsigned long long;

    static Grid squareId(int x, int y) {
        return 1UL << (y * 8 + x);
    }

    bool hasOpenSquare(int x, int y) {
        return 0 == (taken & squareId(x, y));
    }

    SquareStatus square(int x, int y) {
        auto square = squareId(x, y);
        if (taken & square) {
            return (black & square) ? BlackSquare : WhiteSquare;
        }
        else {
            return OpenSquare;
        }
    }

    using Callback = const std::function<void(int, int)>&;

    void ifOpenSquare(int x, int y, Callback f) {
        if (hasOpenSquare(x, y)) {
            f(x, y);
        }
    }

    void findOpenSquaresAround(int x, int y, Callback f);

    using Position = std::pair<int, int>;

    bool play(Player who, int x, int y);
    bool play(Player who, Position pos) {
        return play(who, pos.first, pos.second);
    }

    void print();
    Board &setup(int x, int y, SquareStatus status);

    static Grid reverseBits(Grid v);

private:

    Grid taken; // bit set when a square is taken
    Grid black; // bit set when owner is black

    static Board::Grid flip(Grid taken, Grid black, bool toBlack,
                            int x, int y, int dx, int dy);

    void clear(Grid square) {
        taken &= ~square;
    }

    void takeByBlack(Grid square) {
        taken |= square;
        black |= square;
    }

    void takeByWhite(Grid square) {
        taken |= square;
        black &= ~square;
    }
};

#endif
