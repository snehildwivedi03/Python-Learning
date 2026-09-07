# Sudoku Solver (C++20)

A fast, well-structured Sudoku solver using backtracking with MRV heuristic and constraint propagation.

## Features
- **MRV cell selection** — always fills the most-constrained cell first
- **Candidate bitmask** — O(1) legal-digit lookup per cell
- **Full validation** — row / column / box constraint checking
- **GoogleTest** unit & integration tests
- **Optional sanitizers** — ASan, UBSan, TSan via CMake flag

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

### With sanitizers

```bash
cmake -S . -B build -DSANITIZE=asan -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j$(nproc)
```

## Run

```bash
# Use the built-in hard puzzle
./build/apps/sudoku_app

# Supply your own 81-char puzzle string (0 or . = empty)
./build/apps/sudoku_app 530070000600195000098000060800060003400803001700020006060000280000419005000080079
```

## Test

```bash
ctest --test-dir build --output-on-failure
```

## Docs

```bash
doxygen docs/Doxyfile
```

## Project Structure

```
├── include/sudoku/   # Public headers
│   ├── board.hpp
│   ├── validator.hpp
│   └── engine.hpp
├── src/              # Implementation
├── apps/             # CLI executable
├── tests/            # GoogleTest suites
├── cmake/            # CMake modules (sanitizers)
└── docs/             # Doxygen config
```
