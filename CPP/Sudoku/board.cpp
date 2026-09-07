/**
 * @file board.cpp
 * @brief Implementation of the Board data structure.
 */

#include "sudoku/board.hpp"

#include <cassert>
#include <ostream>
#include <stdexcept>

namespace sudoku {

// ──Board Construction ─────────────────────────────────────────────────────────────

Board::Board() noexcept {
    cells_.fill(0);
}

Board::Board(std::string_view flat) {
    if (flat.size() != static_cast<std::size_t>(kCells)) {
        throw std::invalid_argument(
            "Board string must be exactly 81 characters, got " +
            std::to_string(flat.size()));
    }
    for (int i = 0; i < kCells; ++i) {
        char c = flat[static_cast<std::size_t>(i)];
        if (c == '.' || c == '0') {
            cells_[i] = 0;
        } else if (c >= '1' && c <= '9') {
            cells_[i] = static_cast<int8_t>(c - '0');
        } else {
            throw std::invalid_argument(
                std::string("Unexpected character '") + c + "' at position " +
                std::to_string(i));
        }
    }
}

// ── Element access ────────────────────────────────────────────────────────────

int Board::get(int row, int col) const noexcept {
    assert(row >= 0 && row < kSize);
    assert(col >= 0 && col < kSize);
    return cells_[static_cast<std::size_t>(row * kSize + col)];
}

void Board::set(int row, int col, int digit) noexcept {
    assert(row >= 0 && row < kSize);
    assert(col >= 0 && col < kSize);
    assert(digit >= 0 && digit <= 9);
    cells_[static_cast<std::size_t>(row * kSize + col)] = static_cast<int8_t>(digit);
}

std::optional<std::pair<int, int>> Board::firstEmpty() const noexcept {
    for (int r = 0; r < kSize; ++r) {
        for (int c = 0; c < kSize; ++c) {
            if (get(r, c) == kEmpty) return {{r, c}};
        }
    }
    return std::nullopt;
}

// ── Queries ───────────────────────────────────────────────────────────────────

bool Board::isFull() const noexcept {
    for (auto v : cells_) {
        if (v == kEmpty) return false;
    }
    return true;
}

std::string Board::toFlatString() const {
    std::string s(kCells, '0');
    for (int i = 0; i < kCells; ++i) {
        s[static_cast<std::size_t>(i)] =
            static_cast<char>('0' + cells_[static_cast<std::size_t>(i)]);
    }
    return s;
}

// ── Stream output ─────────────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& os, const Board& board) {
    static constexpr std::string_view kRowSep = "+-------+-------+-------+\n";
    for (int r = 0; r < kSize; ++r) {
        if (r % kBoxSize == 0) os << kRowSep;
        for (int c = 0; c < kSize; ++c) {
            if (c % kBoxSize == 0) os << "| ";
            int v = board.get(r, c);
            if (v == kEmpty) os << ". ";
            else             os << v << ' ';
        }
        os << "|\n";
    }
    os << kRowSep;
    return os;
}

} // namespace sudoku
