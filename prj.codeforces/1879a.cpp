#include <iostream>
#include <vector>

int main() {
    int t = 0;
    std::cin >> t;
    while (t--) {

        int n = 0;
        std::cin >> n;
        std::vector<int> s(n), e(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> s[i] >> e[i];
        }
        
        bool is_winner = true;
        int w = s[0];
        for (int i = 1; i < n; ++i) {
            // нельзя выбрать вес, который поликарп не сможет поднять
            if (s[i] >= w && e[i] >= e[0]) {
                // если есть человек, способный поднять штангу и который
                // делает не меньше поднятий, то никак не победить, потому
                // что вес штанги не увеличить
                is_winner = false;
            }
        }

        if (is_winner) {
            std::cout << w << '\n';
        }
        else {
            std::cout << -1 << '\n';
        }

    }
    return 0;
}