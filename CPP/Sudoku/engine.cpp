/**
 * @file engine.cpp
 * @brief Backtracking solver with MRV heuristic.
 */

#include "sudoku/engine.hpp"
#include "sudoku/validator.hpp"

#include <bit>
#include <climits>
#include <cstdint>

namespace sudoku {

// ── Construction ──────────────────────────────────────────────────────────────

Engine::Engine(SolverOptions opts) noexcept : opts_(std::move(opts)) {}

// ── Public API ────────────────────────────────────────────────────────────────

bool Engine::solve(Board& board) {
    resetStats();

    // Quick sanity check before we start.
    if (!Validator::isBoardValid(board)) return false;

    Board saved = board; // snapshot for restoration on failure
    if (backtrack(board)) return true;

    board = saved; // restore original on failure
    return false;
}

std::optional<Board> Engine::solvedCopy(const Board& board) {
    Board copy = board;
    if (solve(copy)) return copy;
    return std::nullopt;
}

// ── Private helpers ───────────────────────────────────────────────────────────

uint16_t Engine::candidateMask(
        const Board& board, int row, int col) const noexcept {
    // Start with all digits available.
    uint16_t used = 0;

    // Mark digits used in the same row.
    for (int c = 0; c < kSize; ++c) {
        int d = board.get(row, c);
        if (d != kEmpty) used |= static_cast<uint16_t>(1u << (d - 1));
    }
    // Mark digits used in the same column.
    for (int r = 0; r < kSize; ++r) {
        int d = board.get(r, col);
        if (d != kEmpty) used |= static_cast<uint16_t>(1u << (d - 1));
    }
    // Mark digits used in the same 3×3 box.
    int boxRow = (row / kBoxSize) * kBoxSize;
    int boxCol = (col / kBoxSize) * kBoxSize;
    for (int dr = 0; dr < kBoxSize; ++dr) {
        for (int dc = 0; dc < kBoxSize; ++dc) {
            int d = board.get(boxRow + dr, boxCol + dc);
            if (d != kEmpty) used |= static_cast<uint16_t>(1u << (d - 1));
        }
    }

    // Return the complement (available digits), masked to 9 bits.
    return static_cast<uint16_t>((~used) & 0x1FFu);
}

std::pair<int,int> Engine::selectCell(const Board& board) const noexcept {
    int bestCount = INT_MAX;
    std::pair<int,int> best{-1, -1};

    for (int r = 0; r < kSize; ++r) {
        for (int c = 0; c < kSize; ++c) {
            if (board.get(r, c) != kEmpty) continue;

            int count = std::popcount(candidateMask(board, r, c));
            if (count == 0) return {r, c}; // dead end — return immediately
            if (count < bestCount) {
                bestCount = count;
                best = {r, c};
                if (bestCount == 1) return best; // can't do better
            }
        }
    }
    return best;
}

bool Engine::backtrack(Board& board) {
    // Respect iteration limit.
    ++stats_.iterations;
    if (opts_.maxIterations > 0 && stats_.iterations > opts_.maxIterations)
        return false;

    // Board complete?
    auto [row, col] = selectCell(board);
    if (row == -1) {
        // No empty cells left — we have a solution.
        stats_.uniqueSolution = true; // will be refined if !findFirstOnly
        return true;
    }

    uint16_t mask = candidateMask(board, row, col);
    if (mask == 0) {
        // No legal digit for this cell: backtrack.
        ++stats_.backtracks;
        return false;
    }

    // Try each candidate digit (iterate set bits).
    while (mask) {
        // Extract lowest set bit.
        int bit = std::countr_zero(mask);
        mask &= static_cast<uint16_t>(mask - 1); // clear lowest bit

        int digit = bit + 1;
        board.set(row, col, digit);

        if (backtrack(board)) {
            if (opts_.findFirstOnly) return true;
        }
    }

    // Undo and backtrack.
    board.set(row, col, kEmpty);
    ++stats_.backtracks;
    return false;
}

} // namespace sudoku
