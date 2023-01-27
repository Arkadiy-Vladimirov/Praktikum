#include <iostream>


int fibRec(int n) {
    if ((n == 0) || (n == 1)) {
        return 1;
    } else {
        return fibRec(n-1) + fibRec(n-2);
    }
}

int main() {
    int n;
    std::cin >> n;

    std::cout << fibRec(n) << std::endl;

    return 0;
}