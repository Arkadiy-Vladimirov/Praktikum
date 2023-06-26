#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::string unpack(const std::string &str);
int find_digit(const std::string &str);
int find_close(const std::string &str);

std::string max_prefix(const std::vector<std::string> &lines);

std::string operator * (int n, const std::string &str);

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> lines(n);
    for (auto &line : lines) {
        std::cin >> line;
        line = unpack(line);
    }

    std::cout << max_prefix(lines) << std::endl;
    
    return 0;
}



std::string max_prefix(const std::vector<std::string> &lines) {

    std::string max_prefix;
    for (int i = 0; i < lines[0].size(); ++i) {
        char c = lines[0][i];
        
        for (auto &line : lines) {
            if ((i == line.size()) || (line[i] != c)) {
                return max_prefix;
            }
        }
        max_prefix = max_prefix  + c;
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

