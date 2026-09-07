#pragma once

/**
 * @file board.hpp
 * @brief Sudoku board data structures and low-level cell operations.
 */

#include <array>
#include <cstdint>
#include <iosfwd>
#include <optional>
#include <string>

namespace sudoku {

/// Side length of the board (9 for standard Sudoku).
inline constexpr int kSize = 9;

/// Side length of a 3×3 box.
inline constexpr int kBoxSize = 3;

/// Total number of cells.
inline constexpr int kCells = kSize * kSize;

/// Represents an empty cell.
inline constexpr int kEmpty = 0;

/**
 * @brief A flat, value-semantic representation of a 9×9 Sudoku board.
 *
 * Cells are stored in row-major order.  Valid digit values are 1–9; 0 means
 * empty.
 */
class Board {
public:
    // ── Construction ────────────────────────────────────────────────────────

    /// Constructs an all-empty board.
    Board() noexcept;

    /**
     * @brief Constructs a board from an 81-character string.
     *
     * '1'–'9' are treated as filled cells; '0' or '.' denote empty cells.
     * Throws std::invalid_argument if the string length != 81 or contains
     * unexpected characters.
     */
    explicit Board(std::string_view flat);

    // ── Element access ───────────────────────────────────────────────────────

    /// Returns the digit at (row, col); 0 = empty.  Bounds-checked in debug.
    [[nodiscard]] int get(int row, int col) const noexcept;

    /// Sets the cell at (row, col) to @p digit (0–9).
    void set(int row, int col, int digit) noexcept;

    /// Returns the first empty cell, or std::nullopt if the board is full.
    [[nodiscard]] std::optional<std::pair<int, int>> firstEmpty() const noexcept;

    // ── Queries ──────────────────────────────────────────────────────────────

    /// Returns true iff every cell is filled (digit != 0).
    [[nodiscard]] bool isFull() const noexcept;

    /// Serialises the board to a flat 81-character string (digits + '0').
    [[nodiscard]] std::string toFlatString() const;

    // ── Comparison ───────────────────────────────────────────────────────────
    [[nodiscard]] bool operator==(const Board& other) const noexcept = default;

private:
    /// Row-major storage: cells_[row * kSize + col].
    std::array<int8_t, kCells> cells_{};
};

/// Pretty-prints the board with box separators to @p os.
std::ostream& operator<<(std::ostream& os, const Board& board);

} // namespace sudoku
