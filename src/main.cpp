#include <iostream>

static bool IsValid(const int grid[9][9]) {
    int rows[9] = { 0 };
    int cols[9] = { 0 };
    int blocks[9] = { 0 };

    const int FULL_MASK = 0x3FE; // binary 1111111110, bits 1-9 set

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int val = grid[row][col];
            if (val < 1 || val > 9) {
                return false;
            }

            int mask = 1 << val;
            int blockIdx = (row / 3) * 3 + (col / 3);

            // check for duplicates
            if ((rows[row] & mask) || (cols[col] & mask) || (blocks[blockIdx] & mask)) {
                return false;
            }

            rows[row] |= mask;
            cols[col] |= mask;
            blocks[blockIdx] |= mask;
        }
    }

    // check all rows, cols, blocks are exactly 1..9
    for (int i = 0; i < 9; ++i) {
        if (rows[i] != FULL_MASK || cols[i] != FULL_MASK || blocks[i] != FULL_MASK) {
            return false;
        }
    }

    return true;
}

// assume r, c are in range 0..8, val is in range 1..9
static bool TryNum(const int grid[9][9], int row, int col, int value) {
    if (grid[row][col]) {
        return false;
    }

    for (int r = 0; r < 9; ++r) {
        if (r != row && grid[r][col] == value) {
            return false;
        }
    }

    for (int c = 0; c < 9; ++c) {
        if (c != col && grid[row][c] == value) {
            return false;
        }
    }

    int blockRow = (row / 3) * 3;
    int blockCol = (col / 3) * 3;

    for (int dr = 0; dr < 3; ++dr) {
        for (int dc = 0; dc < 3; ++dc) {
            if ((blockRow + dr != row || blockCol + dc != col) &&
                grid[blockRow + dr][blockCol + dc] == value) {
                return false;
            }
        }
    }

    return true;
}

static bool Solve(int grid[9][9]) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid[row][col]) {
                continue;
            }
            for (int i = 1; i <= 9; ++i) {
                if (TryNum(grid, row, col, i)) {
                    grid[row][col] = i;

                    if (Solve(grid)) {
                        return true;
                    }
                    grid[row][col] = 0;
                }
            }
            return false;
        }
    }
    return true;
}

static void PrintGrid(const int grid[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << '\n';
    }
}

int main() {
    int grid[9][9] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 2, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    Solve(grid);
    PrintGrid(grid);
    std::cout << (IsValid(grid) ? "\nCorrect!" : "Incorrect") << "\n";

    return 0;
}
