#include <iostream>
#include <cmath>


int fibRecMod(int n, int k) {
    int F_n = 1;
    if ((n == 0) || (n == 1)) {
    
    } else {
        int prev = 1;
        int preprev = 1;
        for (int i = 2; i <= n; ++i) {
            F_n = (prev + preprev) % int(pow(10,k));
            preprev = prev;
            prev = F_n;
        }
    }
    
    return F_n;
}

int main() {
    int n, k;
    std::cin >> n >> k;

    std::cout << fibRecMod(n, k) << std::endl;

    return 0;
}