// determine if one sequence is a subsequence of another

#include <iostream>
#include <string>
#include <map>

std::map<bool, std::string> bool_to_str {
    {false, "False"},
    {true,  "True" }
};

bool is_subseq(std::string subseq, std::string seq);

int main() {
    std::string s, t;
    std::getline(std::cin, s);
    std::getline(std::cin, t);
    std::cout << bool_to_str[is_subseq(s,t)] << std::endl;
    return 0;
}

//recursive
/*bool is_subseq(std::string subseq, std::string seq) {
    if (subseq == "") {
        return true;
    } else if (seq == "") {
        return false;
    }

    if (subseq[0] == seq[0]) {
        return is_subseq(subseq.substr(1), seq.substr(1));
    } else {
        return is_subseq(subseq, seq.substr(1));
    }
}*/

//iterative
bool is_subseq(std::string subseq, std::string seq) {
    auto subseq_it = subseq.begin(), seq_it = seq.begin();
    
    while ((seq_it != seq.end()) && (subseq_it != subseq.end())) {
        if (*seq_it == *subseq_it) {
            subseq_it++;
        }
        seq_it++;
    }

    return (subseq_it == subseq.end());
}