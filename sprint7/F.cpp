#include <iostream>
#include <vector>

constexpr int MOD = 1000000007;

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> vf(n);

    vf[0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; (j <= k) && ((i-j) >= 0); ++j) {
            vf[i] = (vf[i] + vf[i-j]) % MOD;
        }
    }

    std::cout << vf[n-1] << std::endl;

    return 0;
}