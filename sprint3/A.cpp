// generates all correct bracket sequences of size 2n in lexicographic order

#include <iostream>
#include <string>

void gen_bseq(int open_left, int close_left = 0, std::string prefix = "") {    
    if ((open_left == 0) && (close_left == 0)) {
        std::cout << prefix << std::endl;
    }
    if (open_left != 0) {
        gen_bseq(open_left - 1, close_left + 1, prefix + "(");
    }
    if (close_left != 0) {
        gen_bseq(open_left    , close_left - 1, prefix + ")");
    }
    return;
}

int main() {
    int n;
    std::cin >> n;
    gen_bseq(n);
    return 0;
}