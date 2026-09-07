/**
 * @file main.cpp
 * @brief Interactive Sudoku solver CLI.
 *
 * Usage:
 *   sudoku_app [puzzle_string]
 *
 * puzzle_string — 81 characters, digits 1-9 for given cells, 0 or '.' for
 *                 empty cells.  If omitted, a built-in example is used.
 *
 * Example:
 *   sudoku_app 530070000600195000098000060800060003400803001700020006060000280000419005000080079
 */

#include "sudoku/board.hpp"
#include "sudoku/engine.hpp"
#include "sudoku/validator.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>



// A well-known "hard" puzzle used as the default.
static constexpr std::string_view kDefaultPuzzle =
    "800000000003600000070090200060005030004000100090150708000007906000080010034000005"
    "00";
//   ← 81 chars: "World's hardest Sudoku" by Arto Inkala

int main(int argc, char* argv[]) {
    std::string puzzleStr;

    if (argc >= 2) {
        puzzleStr = argv[1];
    } else {
        puzzleStr = kDefaultPuzzle;
        std::cout << "No puzzle supplied — using Inkala's hard puzzle.\n\n";
    }

    // ── Parse ────────────────────────────────────────────────────────────────
    sudoku::Board board;
    try {
        board = sudoku::Board{puzzleStr};
    } catch (const std::exception& ex) {
        std::cerr << "Error parsing puzzle: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }

    if (!sudoku::Validator::isBoardValid(board)) {
        std::cerr << "The supplied puzzle violates Sudoku constraints.\n";
        return EXIT_FAILURE;
    }

    std::cout << "Puzzle:\n" << board << '\n';

    // ── Solve ─────────────────────────────────────────────────────────────────
    sudoku::Engine engine;
    auto t0 = std::chrono::steady_clock::now();
    bool solved = engine.solve(board);
    auto t1 = std::chrono::steady_clock::now();

    auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();

    // ── Report ────────────────────────────────────────────────────────────────
    const auto& st = engine.stats();
    std::cout << "Iterations : " << st.iterations << '\n';
    std::cout << "Backtracks : " << st.backtracks << '\n';
    std::cout << "Time       : " << us << " µs\n\n";

    if (!solved) {
        std::cout << "No solution found.\n";
        return EXIT_FAILURE;
    }

    std::cout << "Solution:\n" << board << '\n';

    if (!sudoku::Validator::isSolved(board)) {
        std::cerr << "Internal error: solution failed validation!\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
