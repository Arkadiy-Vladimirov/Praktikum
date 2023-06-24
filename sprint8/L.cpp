// Prefix-function computation
//
// Notation:
// string s = s_0s_1...s_{n-1} = s[0, n)
//
// for s: |s| = n > 0 define the prefix-function
// pi(s) = max_{k = 0..n-1} k : s[0, k) = s[n-k, n)
// 
// for i = 1,,n
// pi(i) = pi(s[0,i))
//
// hence, if pi(i) = k, then argmax = s[0..k)
//

#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string s;
    std::getline(std::cin, s);

    int n = s.size();
    std::vector<int> pi(n+1);
    pi[0] = -1; pi[1] = 0;

    for (int i = 1; i < n; ++i) {//go through s, adding new elements one by one

        int k = pi[i];          

        while ((s[i] != s[k]) && (k != 0)) {
            k = pi[k];     //iterate over k - the size of maximum prefix/suffix
        }                  //that may be concat with s[i] to get a new one

        pi[i+1] = k + int(s[i] == s[k]);
    }


    for (int i = 1; i < n + 1; ++i) {
        std::cout << pi[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}