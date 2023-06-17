// accepted parcel ID: -
//
// Problem
//  Given two strings s and t compute the Levenstien distance d(s,t).
//
// Definitions and assumptions                                      // notation
//  1. atomic transform of a string s is one of the following       // a
//          - delete an arbitrary letter                            // del
//          - insert an arbitrary letter                            // ins
//          - replace an arbitrary letter with another              // rep
//  2. we will condsider a class of string transformations that are the 
//     composition of atomic
//  3. for a transform f = a_1 * a_2 * ... * a_n (a-s are atomic) denote the
//     transform complexity |f| = n                                 // |f|
//  4. d(s,t) = min {|f|, f : f(s) = f(t)}                          // d(s,t)
//     note: it may be trivially proven the d(s,t) is indeed a distance
//  5. we denote an empty string as emp. Note that for any string s // emp
//     d(s,emp) = |s|
//
// Statement
//              d(s,t) = min{   d(s1..s{n-1}, t) + 1,
//                              d(s,t_1..t{m-1}) + 1,                        (1)
//                              d(s_1..s_{n-1}, t_1..t_{m-1}) + I(s_n != t_m)
//                          },
//              
// Proof
//  Consider two non empty strings s = s_1s_2...s_n and  t = t_1t_2...t_m and 
// an optimal transform f : f(s) = t, |f| = d(s,t).
//  
//  Consider the last element of s -- s_n. The transform f may have done with it
// one of the following:
//      1. delete s_n. Then f(s) = g(s_1..s_{n-1}) + del(s_n) = t. Where 
//         g(s_1..s{n-1}) = t, and g is optimal, otherwise f would not be. And 
//         we get the following 
//                  d(s,t) = |f| = |g| + |del| = d(s1..s{n-1}, t) + 1
//      2. replace s_n with another letter
//         2.a s_n cannot be replaced with none of the t_1,..t_m, otherwise f
//             is not optimal
//         2.b if s_n is replaced with t_i, i < m (i.e. not the last t letter),
//             then f(s) = g(s) + ins(t_m). Where g(s) = t_1...t_{m-1}, an 
//             optimal transform. Same as in (1) we get
//                  d(s,t) = d(s,t_1..t{m-1}) + 1
//         2.c if s_n is replaced with t_m (the last t letter), then 
//             f(s) = g(s1..s{n-1}) + rep(s_n), where g(s1..s{n-1}) = t1..t{m-1}
//             and rep(s_n) = t_m. Now we get
//                  d(s,t) = d(s_1..s_{n-1}, t_1..t_{m-1}) + I(s_n != t_m),
//             where "I" stays for indicator.
//
//  As these are all of the options, we end up with the formula (1). The 
// optimal f may be recovered as a composition of argmin pair (g,a) of an 
// optimal g and an atomic tranform a.
//
// Algorithm
//  The statement implies the algorithm directly. Given the formula (1) and 
// the base case (def. & ass. 5). We may compute d(s,t) for an arbitrary pair 
// of strings s and t by sequentially computing distance between all prefixes.
//
//  Indeed, we compute a matrix dist of size (n+1)*(m+1) with elements 
// dist[i][j] = d(s_1..s_i, t_1..t_j), where i or j = 0 stays for null prefix.
//  With 0th row and column being initialized according to the (def. & ass. 5),
// the matrix may be computed row by row with direct use of formula (1), i.e.
//              dist[i][j] = min(   dist[i-1][ j ] + 1,
//                                  dist[ i ][j-1] + 1,
//                                  dist[i-1][j-1] + I(s[i] != t[j])
//                      )
//  Clearly, the answer d(s,t) would lie in dist[n][m].
//
// Complexity
//  Space O(nm)*
//  Time O(nm)
//
// * as for the computation of each row only the previous is needed this may be
// easily reduced to O(n) or O(m).
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {

    // input
    std::string s, t;
    std::getline(std::cin, s);
    std::getline(std::cin, t);

    // initialization
    // i = 0..n, j = 0..m - sizes of t and s prefixes corresp.
    int n = s.size(), m = t.size();
    std::vector<std::vector<int>> dist(n+1, std::vector<int>(m+1));

    // base case -- Levenstein distance between the empty string and a string
    // equals to the length of the latter.
    for (int i = 0; i < n+1; ++i) {
        dist[i][0] = i;
    }
    for (int j = 0; j < m+1; ++j) {
        dist[0][j] = j;
    }

    // computation
    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < m+1; ++j) {
            dist[i][j] = std::min({
                dist[i-1][ j ] + 1,                    // "append s_i"
                dist[ i ][j-1] + 1,                    // "delete t_j"
                dist[i-1][j-1] + int(s[i-1] != t[j-1]) // "replace s_i with t_j"
            }); // note that indexing in strings is shifted here and starts at 0
        }
    }

    // output
    std::cout << dist[n][m] << std::endl;

    return 0;
}