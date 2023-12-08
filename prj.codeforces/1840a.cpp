#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {

    int t = 0;
    std::cin >> t;

    while (t--) {

        int n = 0;
        std::cin >> n;
        std::string code = "";
        std::cin >> code;

        std::vector<std::pair<char, int>> res;
        res.push_back({ code[0], 1 });

        for (int i = 1; i < n; ++i) {
            if (res.back().second==2) {
                res.push_back({ code[i],1 });
            }
            else if (code[i]==res.back().first) {
                res.back().second += 1;
            }
        }

        for (int i = 0; i < res.size(); ++i) {
            std::cout << res[i].first;
        }
        std::cout << "\n";

    }

    return 0;
}