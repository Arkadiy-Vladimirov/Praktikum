// accepted parcel ID: 88623546
//
// Problem: 
//  Given n formulas get the maximum common prefix of strings this formulas 
// define. The size of strings is guaranteed to be less than m.
//  Here, formula is a random algebraic expression on strings where sum is a 
// string concatenation and multiplication with a number x is a concatenation 
// of x copies of a string.
//
// Solution:
//  The algorithm simply computes the formulas and finds the greatest common 
// prefix as the greatest common prefix of the minimum and the maximum strings 
// (in lexicographical order).
//
//  The first part recursively costructs a string. To construct another 
// symbol it would need O(1) time, resulting in O(m) for the whole string and 
// O(nm) for all. It would also use O(m) space to support call stack and for 
// auxilary string operations.
//  To find the greatest common prefix of two strings O(m) operations would be
// performed. And to find the maximum and the minimum strings another O(nm) 
// operations are needed.
//
// Memory usage: O(nm)
// Time consumption: O(nm)
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::string unpack(const std::string &str);
int find_digit(const std::string &str);
int find_close(const std::string &str);

std::string max_common_prefix(const std::string &a, const std::string &b);

std::string operator * (int n, const std::string &str);

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> lines(n);
    for (auto &line : lines) {
        std::cin >> line;
        line = unpack(line);
    }

    std::string max_line = *std::max_element(lines.begin(), lines.end());
    std::string min_line = *std::min_element(lines.begin(), lines.end());
    
    std::cout << max_common_prefix(min_line, max_line) << std::endl;

    return 0;
}



std::string max_common_prefix(const std::string &a, const std::string &b) {

    std::string max_prefix;
    for (int i = 0; i < std::min(a.size(), b.size()); ++i) {
        if (a[i] != b[i]) {
            return max_prefix;
        }
        max_prefix = max_prefix + a[i];
    }
    
    return max_prefix;
}


std::string unpack(const std::string &str) {

    if (std::isdigit(str[0])) {
        int times = str[0] - '0';
        int pos = find_close(str);

        return  times * unpack(str.substr(2, pos - 2)) 
                + unpack(str.substr(pos + 1));
    }

    int pos = find_digit(str);

    if (pos != str.size()) {
        return str.substr(0, pos) + unpack(str.substr(pos));
    }

    return str;
}

std::string operator * (int n, const std::string &str) {
    std::string prod;
    for (int i = 0; i < n; ++i) {
        prod.append(str);
    }
    return prod;
}

int find_digit(const std::string &str) {
    int pos;
    for (pos = 0; pos < str.size(); ++pos) {
        if (std::isdigit(str[pos])) {
            break;
        }
    }
    return pos;
}

int find_close(const std::string &str) {
    int pos = 1; // skip digit
    int open = 1;
    
    while (open != 0) {
        pos++;  // skip '['
        if (str[pos] == '[') {
            open++;
        }
        if (str[pos] == ']') {
            open--;
        }
    }
    return pos;
}

