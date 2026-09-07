#include <cstdio>   // for snprintf
#include <cstring>  // for strlen
#include <iostream>

int main() {
    char buffer[20];
    int age = 25;
    const char* name = "Jonathan";

    // Safe formatting
    int written = snprintf(buffer, sizeof(buffer), "Name: %s, Age: %d", name, age);

    if (written < 0) {
        std::cerr << "Formatting error!\n";
    } else if (written >= (int)sizeof(buffer)) {
        std::cout << "Output was truncated! Needed " << written + 1 << " bytes.\n";
    }

    std::cout << "Buffer content: \"" << buffer << "\"\n";
    return 0;
}
