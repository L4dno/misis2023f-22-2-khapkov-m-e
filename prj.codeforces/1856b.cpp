#include <iostream>
#include <set>
#include <algorithm>

int main() {
    int t = 0;
    std::cin >> t;
    while (t--) {

        std::set<int> nums;
        int n = 0;
        std::cin >> n;
        
        int tmp = 0;
        long long sum = 0;
        // input
        for (int i = 0; i < n; ++i) {
            std::cin >> tmp;
            sum += tmp;
            nums.insert(tmp);
        }
        if (1 == n) {
            std::cout << "NO\n";
            continue;
        }

        // finding min excluded
        int mex = 0;
        for (int i = 1;; ++i) {
            if (nums.find(i) == nums.end()) {
                mex = i;
                break;
            }
        }
        // cant get less sum than A
        // a contains all [1,n] or all equals
        int max =  *(prev(nums.end())) ;
        if (mex>=max && nums.size()<n) {
            std::cout << "NO\n";
        }
        else {
            std::cout << "YES\n";
        }

    }
    return 0;
}