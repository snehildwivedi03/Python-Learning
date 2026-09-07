#include <iostream>

/**
 * Generates a hollow diamond pattern based on user input n.
 * n represents the number of rows in the upper half (including the middle).
 * The total height of the diamond is 2n - 1.
 */
int main() {
    int n;
    std::cout << "Enter the number of rows for the upper half of the diamond (positive integer): ";
    std::cin >> n;
    if (!(std::cin >> n) || n <= 0) {
        return 1;
    }

    // Upper Half of the Diamond (Rows 1 to n)
    for (int i = 1; i <= n; i++) {
        // Leading Spaces: (n - i) spaces to center the row
        for (int j = 1; j <= n - i; j++) {
            std::cout << " ";
        }

        // Star and Internal Space Logic
        for (int j = 1; j <= (2 * i - 1); j++) {
            if (j == 1 || j == (2 * i - 1)) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    // Lower Half of the Diamond (Rows n-1 down to 1)
    for (int i = n - 1; i >= 1; i--) {
        // Leading Spaces: (n - i) spaces
        for (int j = 1; j <= n - i; j++) {
            std::cout << " ";
        }

        // Star and Internal Space Logic
        for (int j = 1; j <= (2 * i - 1); j++) {
            if (j == 1 || j == (2 * i - 1)) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    return 0;
}