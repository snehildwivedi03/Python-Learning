#pragma once

/**
 * @file validator.hpp
 * @brief Sudoku rule-checking utilities.
 */

#include "board.hpp"

namespace sudoku {

/**
 * @brief Stateless collection of Sudoku constraint-checking functions.
 *
 * All functions operate on a @ref Board and are pure (no side-effects).
 */
class Validator {
public:
    Validator() = delete; // pure utility class

    /**
     * @brief Returns true iff placing @p digit at (row, col) violates no
     *        Sudoku constraint (row, column, or 3×3 box).
     *
     * The cell at (row, col) itself is ignored so the function works both for
     * empty and already-filled cells (useful during board construction).
     */
    [[nodiscard]] static bool isPlacementValid(
        const Board& board, int row, int col, int digit) noexcept;

    /// Returns true iff @p row (0-indexed) contains no duplicate digits.
    [[nodiscard]] static bool isRowValid(const Board& board, int row) noexcept;

    /// Returns true iff @p col (0-indexed) contains no duplicate digits.
    [[nodiscard]] static bool isColValid(const Board& board, int col) noexcept;

    /**
     * @brief Returns true iff the 3×3 box containing (row, col) has no
     *        duplicate digits.
     */
    [[nodiscard]] static bool isBoxValid(
        const Board& board, int row, int col) noexcept;

    /**
     * @brief Returns true iff the entire board satisfies all Sudoku
     *        constraints (rows, columns, and boxes).
     *
     * An empty board is considered valid.
     */
    [[nodiscard]] static bool isBoardValid(const Board& board) noexcept;

    /**
     * @brief Returns true iff the board is completely and correctly solved:
     *        every cell is filled and all constraints are satisfied.
     */
    [[nodiscard]] static bool isSolved(const Board& board) noexcept;
};

} // namespace sudoku
