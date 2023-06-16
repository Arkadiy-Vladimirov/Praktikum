// accepted parcel ID: -
//
// Problem description
//
// Solution
//

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, sum = 0;
    std::cin >> n;

    std::vector<int> x(n+1);
    for (int i = 1; i < n+1; ++i) {
        std::cin >> x[i];
        sum += x[i];
    }
    
    std::vector<int> v_prev_i(sum/2 + 1, 0);
    std::vector<int> v_curr_i(sum/2 + 1, 0);

    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < sum/2 + 1; ++j) {
            if ((j - x[i]) < 0) { // if x[i] does not fit into the knapsack
                v_curr_i[j] = v_prev_i[j];              // v(i-1, j)
            } else {
                v_curr_i[j] = std::max(
                                v_prev_i[j],            // v(i-1, j)
                                v_prev_i[j-x[i]] + x[i] // v(i-1, j-x[i]) + x[i]
                );
            }
        } 
        std::copy(v_curr_i.begin(), v_curr_i.end(), v_prev_i.begin());
    }   

    if (v_curr_i[sum/2] == (sum/2 + sum%2)) {
        std::cout << "True"  << std::endl;
    } else {
        std::cout << "False" << std::endl;
    }

    return 0;
}