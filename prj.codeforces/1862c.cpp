#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n_inputs = 0;
    std::cin >> n_inputs;
    while (0!= n_inputs--) {
        int n_planks = 0;
        std::cin >> n_planks;
        std::vector<int> planks(n_planks, 0);
        for (int i_plank = 0; i_plank < n_planks; ++i_plank) {
            std::cin >> planks[i_plank];
        }
        if (planks[0] > n_planks) {
            std::cout << "NO\n";
            continue;
        }

        for (int i = n_planks; i >= 1; --i) {

        }

        

    }
    return 0;
}