/**
 * @file validator.cpp
 * @brief Implementation of Sudoku constraint checking.
 */

#include "sudoku/validator.hpp"

#include <array>
#include <cstdint>

namespace sudoku {

namespace {

/// Returns a 9-bit presence mask for the given cells.
/// Bit i (0-indexed) is set iff digit (i+1) appears in the span.
/// Returns 0xFFFF on duplicate detection (used internally).
uint16_t presenceMask(const Board& board,
                      const std::pair<int,int> (&cells)[kSize]) {
    uint16_t seen = 0;
    for (auto [r, c] : cells) {
        int d = board.get(r, c);
        if (d == kEmpty) continue;
        uint16_t bit = static_cast<uint16_t>(1u << (d - 1));
        if (seen & bit) return 0xFFFF; // duplicate
        seen |= bit;
    }
    return seen;
}

} // namespace

// ── Placement check ───────────────────────────────────────────────────────────

bool Validator::isPlacementValid(
        const Board& board, int row, int col, int digit) noexcept {
    // Check row
    for (int c = 0; c < kSize; ++c) {
        if (c != col && board.get(row, c) == digit) return false;
    }
    // Check column
    for (int r = 0; r < kSize; ++r) {
        if (r != row && board.get(r, col) == digit) return false;
    }
    // Check 3×3 box
    int boxRow = (row / kBoxSize) * kBoxSize;
    int boxCol = (col / kBoxSize) * kBoxSize;
    for (int dr = 0; dr < kBoxSize; ++dr) {
        for (int dc = 0; dc < kBoxSize; ++dc) {
            int r = boxRow + dr, c = boxCol + dc;
            if (r == row && c == col) continue;
            if (board.get(r, c) == digit) return false;
        }
    }
    return true;
}

// ── Row / column / box checks ─────────────────────────────────────────────────

bool Validator::isRowValid(const Board& board, int row) noexcept {
    uint16_t seen = 0;
    for (int c = 0; c < kSize; ++c) {
        int d = board.get(row, c);
        if (d == kEmpty) continue;
        uint16_t bit = static_cast<uint16_t>(1u << (d - 1));
        if (seen & bit) return false;
        seen |= bit;
    }
    return true;
}

bool Validator::isColValid(const Board& board, int col) noexcept {
    uint16_t seen = 0;
    for (int r = 0; r < kSize; ++r) {
        int d = board.get(r, col);
        if (d == kEmpty) continue;
        uint16_t bit = static_cast<uint16_t>(1u << (d - 1));
        if (seen & bit) return false;
        seen |= bit;
    }
    return true;
}

bool Validator::isBoxValid(const Board& board, int row, int col) noexcept {
    uint16_t seen = 0;
    int boxRow = (row / kBoxSize) * kBoxSize;
    int boxCol = (col / kBoxSize) * kBoxSize;
    for (int dr = 0; dr < kBoxSize; ++dr) {
        for (int dc = 0; dc < kBoxSize; ++dc) {
            int d = board.get(boxRow + dr, boxCol + dc);
            if (d == kEmpty) continue;
            uint16_t bit = static_cast<uint16_t>(1u << (d - 1));
            if (seen & bit) return false;
            seen |= bit;
        }
    }
    return true;
}

bool Validator::isBoardValid(const Board& board) noexcept {
    for (int i = 0; i < kSize; ++i) {
        if (!isRowValid(board, i)) return false;
        if (!isColValid(board, i)) return false;
    }
    for (int br = 0; br < kSize; br += kBoxSize) {
        for (int bc = 0; bc < kSize; bc += kBoxSize) {
            if (!isBoxValid(board, br, bc)) return false;
        }
    }
    return true;
}

bool Validator::isSolved(const Board& board) noexcept {
    return board.isFull() && isBoardValid(board);
}

} // namespace sudoku
