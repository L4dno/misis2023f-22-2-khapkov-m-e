#include <iostream>

int main() {
    int t = 0;
    std::cin >> t;
    while (t--) {

        int n = 0;
        std::cin >> n;
        if (n <= 4) {
            std::cout << "Bob\n";
        }
        else {
            std::cout << "Alice\n";
        }

    }
    return 0;
}