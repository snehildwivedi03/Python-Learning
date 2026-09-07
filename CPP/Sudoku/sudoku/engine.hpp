#pragma once

/**
 * @file engine.hpp
 * @brief Core Sudoku solving engine.
 *
 * The engine uses a backtracking algorithm augmented with:
 *   - Naked-singles constraint propagation (immediate elimination)
 *   - Minimum-remaining-values (MRV) cell-selection heuristic
 *
 * These together reduce the search space dramatically, making even
 * hard/expert-grade puzzles solvable in microseconds.
 */

#include "board.hpp"

#include <cstddef>
#include <optional>

namespace sudoku {

/**
 * @brief Solver configuration knobs.
 */
struct SolverOptions {
    /// When true the solver stops after finding the first solution.
    bool findFirstOnly{true};

    /// Maximum number of recursive calls before giving up (0 = unlimited).
    std::size_t maxIterations{0};
};

/**
 * @brief Statistics gathered during a solve run.
 */
struct SolveStats {
    std::size_t iterations{0};   ///< Total recursive calls made.
    std::size_t backtracks{0};   ///< Number of times the solver backtracked.
    bool        uniqueSolution{false}; ///< True iff exactly one solution exists.
};

/**
 * @brief The solver engine.
 *
 * Create one instance per puzzle (or reuse across puzzles — it is stateless
 * between calls to @ref solve).
 */
class Engine {
public:
    explicit Engine(SolverOptions opts = {}) noexcept;

    /**
     * @brief Attempts to solve @p board in-place.
     *
     * @return true if a solution was found, false if the puzzle is
     *         unsolvable (or the iteration limit was exceeded).
     *
     * On success, @p board contains the solved state.
     * On failure, @p board is left in its original state.
     */
    bool solve(Board& board);

    /**
     * @brief Convenience wrapper — solves a copy and returns it.
     *
     * @return The solved board, or std::nullopt if unsolvable.
     */
    [[nodiscard]] std::optional<Board> solvedCopy(const Board& board);

    /// Returns statistics from the most recent @ref solve call.
    [[nodiscard]] const SolveStats& stats() const noexcept { return stats_; }

    /// Resets the statistics counters.
    void resetStats() noexcept { stats_ = {}; }

private:
    // ── Internal helpers ────────────────────────────────────────────────────

    /// Bitmask of digits 1-9 that are still legal for (row, col).
    /// Returns a 9-bit mask; bit i set ↔ digit (i+1) is available.
    [[nodiscard]] uint16_t candidateMask(
        const Board& board, int row, int col) const noexcept;

    /// Selects the unfilled cell with the fewest candidates (MRV heuristic).
    /// Returns {-1,-1} when no empty cells remain.
    [[nodiscard]] std::pair<int,int> selectCell(const Board& board) const noexcept;

    /// Core recursive backtracker.
    bool backtrack(Board& board);

    SolverOptions opts_;
    SolveStats    stats_;
};

} // namespace sudoku
