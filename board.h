#ifndef BOARD_H
#define BOARD_H

#include <functional>

class Board {
public:
    using Position = std::pair<int, int>;

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
        owner = GRID(00000000,
                     00000000,
                     00000000,
                     00001000,
                     00010000,
                     00000000,
                     00000000,
                     00000000);
    }

    void setup(char *state);

    bool hasOpenSquare(int x, int y) {
        return 0 == (taken & bit(x, y));
    }

    SquareStatus square(int x, int y) {
        auto mask = bit(x, y);
        if (taken & mask) {
            return (owner & mask) ? BlackSquare : WhiteSquare;
        }
        else {
            return OpenSquare;
        }
    }

    using Callback = const std::function<void(int, int)>&;

    void ifOpenSquare(int x, int y, Callback f);
    void findOpenSquaresAround(int x, int y, Callback f);

    bool play(Player who, int x, int y);
    bool play(Player who, Position pos) {
        return play(who, pos.first, pos.second);
    }

    void print();
    Board &setup(int x, int y, SquareStatus status);

    using Grid = unsigned long long;

    static Grid bit(int x, int y) {
        return 1L << (y * 8 + x);
    }

    static Grid reverseBits(Grid v);

private:

    Grid taken; // bit set when a square is taken
    Grid owner; // bit set when owner is black

    static Grid flip(Grid taken, Grid owner, bool toBlack,
                     int x, int y, int dx, int dy);
};

#endif
