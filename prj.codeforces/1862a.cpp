#include <iostream>
#include <vector>

int FindLeftOccurence(const std::vector<std::vector<char>>& carp,
    char exp, int bound) {
    if (bound == carp[0].size()) {
        return bound;
    }
    int min_j = carp[0].size();
    for (int i = 0; i < carp.size(); ++i) {
        for (int j = bound + 1; j < carp[0].size(); ++j) {
            if (carp[i][j] == exp && j < min_j) {
                min_j = j;
            }
        }
    }
    return min_j;
}

int main() {
    int t = 0;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<char>> c(n, std::vector<char>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                std::cin >> c[i][j];
            }
        }

        int bound = -1;
        bound = FindLeftOccurence(c, 'v', bound);
        bound = FindLeftOccurence(c, 'i', bound);
        bound = FindLeftOccurence(c, 'k', bound);
        bound = FindLeftOccurence(c, 'a', bound);

        if (m != bound) {
            std::cout << "YES\n";
        }
        else {
            std::cout << "NO\n";
        }
    }
    return 0;
}