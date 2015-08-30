#include "game.h"
#include "gtest/gtest.h"

TEST(GameTest, InitialState) {
    Game g;
    EXPECT_EQ(Board::White, g.square(3, 3));
    EXPECT_EQ(Board::Black, g.square(3, 4));
}

TEST(GameTest, SimplePlay) {
    Game g;
    EXPECT_TRUE(g.play(Board::Black, 3, 2));
    EXPECT_TRUE(g.play(Board::White, 2, 4));
    EXPECT_EQ(Board::White, g.square(2, 4));
    EXPECT_EQ(Board::White, g.square(3, 4));
}
