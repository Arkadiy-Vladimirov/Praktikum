#include <iostream>
#include <vector>

constexpr int MOD = 1000000007;

int main() {
    int n;
    std::cin >> n;

    std::vector<int> fibonacci(n+2, 0);
    fibonacci[0] = 1;
    
    for (int i = 0; i < n; ++i) {
        fibonacci[i+1] = (fibonacci[i+1] + fibonacci[i]) % MOD;
        fibonacci[i+2] = (fibonacci[i+2] + fibonacci[i]) % MOD;
    }

    std::cout << fibonacci[n] << std::endl;

    return 0;
}
