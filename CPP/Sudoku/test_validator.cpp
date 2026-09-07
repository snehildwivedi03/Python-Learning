/**
 * @file test_validator.cpp
 * @brief Unit tests for the Validator rule-checking functions.
 */

#include "sudoku/board.hpp"
#include "sudoku/validator.hpp"

#include <gtest/gtest.h>

using namespace sudoku;

// ── Helpers ───────────────────────────────────────────────────────────────────

static Board allZeros() { return Board{}; }

static Board makeBoard(std::string_view s) { return Board{s}; }

// ── isPlacementValid ──────────────────────────────────────────────────────────

TEST(ValidatorTest, PlacementValidOnEmptyBoard) {
    Board b = allZeros();
    for (int d = 1; d <= 9; ++d) {
        EXPECT_TRUE(Validator::isPlacementValid(b, 0, 0, d));
    }
}

TEST(ValidatorTest, PlacementInvalidDuplicateInRow) {
    Board b = allZeros();
    b.set(0, 3, 5);
    EXPECT_FALSE(Validator::isPlacementValid(b, 0, 7, 5));
}

TEST(ValidatorTest, PlacementInvalidDuplicateInCol) {
    Board b = allZeros();
    b.set(4, 2, 3);
    EXPECT_FALSE(Validator::isPlacementValid(b, 8, 2, 3));
}

TEST(ValidatorTest, PlacementInvalidDuplicateInBox) {
    Board b = allZeros();
    b.set(0, 0, 7);
    EXPECT_FALSE(Validator::isPlacementValid(b, 2, 2, 7));
    EXPECT_TRUE(Validator::isPlacementValid(b, 0, 3, 7)); // different box
}

TEST(ValidatorTest, PlacementIgnoresOwnCell) {
    Board b = allZeros();
    b.set(4, 4, 9);
    // Placing 9 at (4,4) should be OK (same digit, same cell ignored).
    EXPECT_TRUE(Validator::isPlacementValid(b, 4, 4, 9));
}

// ── isRowValid ────────────────────────────────────────────────────────────────

TEST(ValidatorTest, EmptyRowIsValid) {
    EXPECT_TRUE(Validator::isRowValid(allZeros(), 0));
}

TEST(ValidatorTest, FullUniqueRowIsValid) {
    Board b = allZeros();
    for (int c = 0; c < kSize; ++c) b.set(0, c, c + 1);
    EXPECT_TRUE(Validator::isRowValid(b, 0));
}

TEST(ValidatorTest, DuplicateInRowIsInvalid) {
    Board b = allZeros();
    b.set(2, 0, 4);
    b.set(2, 8, 4);
    EXPECT_FALSE(Validator::isRowValid(b, 2));
}

// ── isColValid ────────────────────────────────────────────────────────────────

TEST(ValidatorTest, EmptyColIsValid) {
    EXPECT_TRUE(Validator::isColValid(allZeros(), 0));
}

TEST(ValidatorTest, DuplicateInColIsInvalid) {
    Board b = allZeros();
    b.set(1, 5, 6);
    b.set(7, 5, 6);
    EXPECT_FALSE(Validator::isColValid(b, 5));
}

// ── isBoxValid ────────────────────────────────────────────────────────────────

TEST(ValidatorTest, EmptyBoxIsValid) {
    EXPECT_TRUE(Validator::isBoxValid(allZeros(), 0, 0));
}

TEST(ValidatorTest, DuplicateInBoxIsInvalid) {
    Board b = allZeros();
    b.set(3, 3, 2);
    b.set(5, 5, 2);
    EXPECT_FALSE(Validator::isBoxValid(b, 3, 3));
}

// ── isBoardValid ─────────────────────────────────────────────────────────────

TEST(ValidatorTest, EmptyBoardIsValid) {
    EXPECT_TRUE(Validator::isBoardValid(allZeros()));
}

TEST(ValidatorTest, PartiallyFilledValidBoardIsValid) {
    auto board = makeBoard(
        "530070000"
        "600195000"
        "098000060"
        "800060003"
        "400803001"
        "700020006"
        "060000280"
        "000419005"
        "000080079");
    EXPECT_TRUE(Validator::isBoardValid(board));
}

TEST(ValidatorTest, InvalidBoardDetected) {
    Board b = allZeros();
    b.set(0, 0, 1);
    b.set(0, 1, 1); // duplicate in row 0
    EXPECT_FALSE(Validator::isBoardValid(b));
}

// ── isSolved ─────────────────────────────────────────────────────────────────

TEST(ValidatorTest, SolvedBoardIsSolved) {
    auto board = makeBoard(
        "534678912"
        "672195348"
        "198342567"
        "859761423"
        "426853791"
        "713924856"
        "961537284"
        "287419635"
        "345286179");
    EXPECT_TRUE(Validator::isSolved(board));
}

TEST(ValidatorTest, EmptyBoardIsNotSolved) {
    EXPECT_FALSE(Validator::isSolved(allZeros()));
}

TEST(ValidatorTest, PartialBoardIsNotSolved) {
    auto board = makeBoard(
        "530070000"
        "600195000"
        "098000060"
        "800060003"
        "400803001"
        "700020006"
        "060000280"
        "000419005"
        "000080079");
    EXPECT_FALSE(Validator::isSolved(board));
}

// ── Board construction edge cases ─────────────────────────────────────────────

TEST(BoardTest, ParsesDotAsEmpty) {
    auto board = makeBoard(
        "........1"
        "........."
        "........."
        "........."
        "........."
        "........."
        "........."
        "........."
        ".........");
    EXPECT_EQ(board.get(0, 8), 1);
    EXPECT_EQ(board.get(0, 0), 0);
}

TEST(BoardTest, ThrowsOnBadLength) {
    EXPECT_THROW(Board{"123"}, std::invalid_argument);
}

TEST(BoardTest, ThrowsOnBadCharacter) {
    std::string bad(81, '0');
    bad[10] = 'X';
    EXPECT_THROW(Board{bad}, std::invalid_argument);
}
