// generates all correct bracket sequences of size 2n in lexicographic (incorrect) order

#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> generate_bracket_sequences(int n) {
    std::vector<std::string> sequences_n;

    if (n == 0) {
        sequences_n.push_back("");
    }

    for (int k = 0; k < n; ++k) {
        auto sequences_n_k_1 = generate_bracket_sequences(n-k-1);
        auto sequences_k = generate_bracket_sequences(k);
        for (auto first_sequence : sequences_n_k_1) {
            for (auto second_sequence : sequences_k) {
                sequences_n.push_back("(" + first_sequence + ")" + second_sequence);
            }
        }
    }

    return sequences_n;
}

int main() {
    int n;
    std::cin >> n;
    auto bracket_sequences = generate_bracket_sequences(n);
    for (auto sequence : bracket_sequences) {
        std::cout << sequence << std::endl;
    }
    return 0;
}