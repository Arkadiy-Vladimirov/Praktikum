// accepted parcel ID: 88300410
//
// Problem
//  Given an array X = x_1, ... x_n of numbers, 0 <= x_i <= m for all i,
// define if there is a disjunctive partition of X with equal sum of elements, 
// i.e. Y \in X and Z \in X, s.t. Y \union Z = X and sum(Y) = sum(Z).
// 
// Solution
//  As Z = X / Y and sum(Z) = sum(X) - sum(Y), sum(Y) = sum(Z) iff
// sum(Y) = sum(Z) = 1/2 sum(X). 
//  We would set the constant C = 1/2 sum(X) <= nm/2 and the initial problem is 
// equivalent to the following: 
//                  define if there is a subset Y of X such that sum(Y) = C.
//
//  This reduces the problem to the classical knapsack problem. We consider 
// numbers x_i as items (of cost and weight x_i) and try to pack a knapsack of 
// capacity C. The answer to the initial problem is positive iff the maximum 
// cost of a set items that may fit into the knapsack of capacity C is indeed C.
//
//  A small reminder of the knapsack problem solution: we initialize a value 
// matrix v of size (n+1)*(C+1) with elements 
//      v[i][j] = max_{value(Y) : Y \in X_i, s.t. weight(Y) <= j}
// the sequence of increasing subsets 
//      (X_0 = \empty) \in (X_1 = {x_1}) \in ... \in (X_n = {x_1, ... x_n}),
// allow us to compute the matrix with the following formula
//  v[i][j] = max(  v[i-1][j],           -- we don't take the new element x_i
//                  v[i][j-weight(x_i)]) -- we take the new element but have to 
//                                  fit the others into j - weight(x_i) capacity
//      {in our case weight and costs are same so the formula is even simplier}
// 
//  This implies the matrix computation procedure: with v[0][j] and v[i][0] 
// being initialized as 0 (no items to put or no capacity to fill) we go 
// through the matrix row by row filling the cells according to the formula 
// above.
//  The answer would lie in v[n][C] cell.
//  The complexity follows from the procedure:
//      O(nC) = O(n^2 m) in space *
//      O(nC) = O(n^2 m) in time
// 
//  * as for the computation of another row only the values from the previous 
// one are used, the space complexity of the procedure may be easily reduced to 
// O(C) = O(nm) as it is done in the code below.
//

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, sumX = 0;
    std::cin >> n;

    std::vector<int> x(n+1);
    for (int i = 1; i < n+1; ++i) {
        std::cin >> x[i];
        sumX += x[i];
    }
    
    std::vector<int> v_prev(sumX/2 + 1, 0); // previous row
    std::vector<int> v_curr(sumX/2 + 1, 0); // current  row

    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < sumX/2 + 1; ++j) {
            if ((j - x[i]) < 0) { // if x[i] does not fit into the knapsack
                v_curr[j] = v_prev[j];               // := v(i-1, j)
            } else {
                v_curr[j] = std::max(
                                v_prev[j],           // := v(i-1, j)
                                v_prev[j-x[i]] + x[i]// := v(i-1, j-x[i]) + x[i]
                );
            }
        } 
        std::copy(v_curr.begin(), v_curr.end(), v_prev.begin());
    }   

    if (v_curr[sumX/2] == (sumX/2 + sumX%2)) {
        std::cout << "True"  << std::endl;
    } else {
        std::cout << "False" << std::endl;
    }

    return 0;
}