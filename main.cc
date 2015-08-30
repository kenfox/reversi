#include "board.h"

auto main() -> int {
    Board b; b.print();
    b.play(Board::Black, 3, 2); b.print();
    b.play(Board::White, 2, 4); b.print();
    return 0;
}
