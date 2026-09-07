/**
 * @file test_solver.cpp
 * @brief Unit and integration tests for the Engine (solver).
 */

#include "sudoku/board.hpp"
#include "sudoku/engine.hpp"
#include "sudoku/validator.hpp"

#include <gtest/gtest.h>
#include <string_view>

using namespace sudoku;

// ── Helpers ──────────────────────────────────────────────────────────────────

static Board makeBoard(std::string_view s) { return Board{s}; }

// ── Basic solve tests ─────────────────────────────────────────────────────────

TEST(EngineTest, SolvesEasyPuzzle) {
    // A well-known easy puzzle
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

    Engine engine;
    ASSERT_TRUE(engine.solve(board));
    EXPECT_TRUE(Validator::isSolved(board));
}

TEST(EngineTest, SolvesHardPuzzle) {
    // Arto Inkala's "World's hardest Sudoku"
    auto board = makeBoard(
        "800000000"
        "003600000"
        "070090200"
        "060005030"
        "004000100"
        "090150708"
        "000007906"
        "000080010"
        "034000005"
        "00"          // <- this makes it 81 chars, oops — pad correctly
    );
    // Use correct 81-char string:
    board = makeBoard(
        "80000000"  "0"
        "00360000"  "0"
        "07009020"  "0"
        "06000503"  "0"
        "00400010"  "0"
        "09015070"  "8"
        "00000790"  "6"
        "00008001"  "0"
        "03400000"  "5");

    Engine engine;
    ASSERT_TRUE(engine.solve(board));
    EXPECT_TRUE(Validator::isSolved(board));
}

TEST(EngineTest, ReturnsNulloptForUnsolvable) {
    // Row 0 has two 1s — immediately invalid
    auto board = makeBoard(
        "110000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000");

    Engine engine;
    EXPECT_FALSE(engine.solve(board));
}

TEST(EngineTest, SolvedCopyLeavesOriginalUnchanged) {
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

    Board original = board;
    Engine engine;
    auto result = engine.solvedCopy(board);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(board, original); // original untouched
    EXPECT_TRUE(Validator::isSolved(*result));
}

TEST(EngineTest, AlreadySolvedBoardReturnsTrueImmediately) {
    // Pre-solved board (easy puzzle solution)
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

    Engine engine;
    EXPECT_TRUE(engine.solve(board));
    EXPECT_EQ(engine.stats().iterations, 1u); // should exit on first call
}

TEST(EngineTest, EmptyBoardIsSolvable) {
    Board board; // all zeros
    Engine engine;
    ASSERT_TRUE(engine.solve(board));
    EXPECT_TRUE(Validator::isSolved(board));
}

TEST(EngineTest, StatsAreRecordedCorrectly) {
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

    Engine engine;
    engine.solve(board);

    EXPECT_GT(engine.stats().iterations, 0u);
}
