// find the number of all possible binary search trees with keys 1 .. n
//
// The idea is as follows.
// Say we have n ordered points and we try to connect them in a bin search tree.
//
//                  ..<-|->..
//  o   o   o       o   o   o       o   o
//  1   2   3   ... k-1 k   k+1 ... n-1 n
//
// Choose a root k and the dots are separated into two nonintersecting 
// classes (as follows from the definition of bin search tree) that must form 
// two independent trees and be connected with the root with one edge each.
// Thus it is left to costruct two arbitrary edges one to the left, one to 
// the right, which is equal of chossing another pair of roots for trees of 
// corresponding sizes.
//
//                  |<-..   ..<-|->..   ..->|
//  o   o   o       o       o   o   o       o       o   o
//  1   2   3   ... k_l ... k-1 k   k+1 ... k_r ... n-1 n
// 
// And we come to a recurrent formula of tree card p for given number of dots n:
// p(0) = 1, p(1) = 1;
// p(n) = \sum_{k=1}^{k=n} p(k-1)*p(n-k).                    
//

#include <iostream>

int p(int n) {
    if ((n == 0) || (n == 1)) {
        return 1;
    }
    
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        sum += p(k-1)*p(n-k);
    }
    return sum;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << p(n) << std::endl;
}