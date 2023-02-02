// find the position of the first element in array greater or equal than x

#include <iostream>

int find_first_ge_num(int x, int idx_begin, int idx_end, int* arr) {
    if ((idx_end - idx_begin) == 1) {//if only one element left
        if (arr[idx_begin] >= x) {
            return idx_begin + 1; //return number, not index!
        } else {
            return -1;
        }
    }

    int idx_middle = (idx_begin + idx_end - 1) / 2;
    if (arr[idx_middle] < x) {
        return find_first_ge_num(x, idx_middle + 1, idx_end, arr);
    } else {
        return find_first_ge_num(x, idx_begin, idx_middle + 1, arr);
    }
}

int main() {
    int n, x;
    std::cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::cin >> x;

    std::cout << find_first_ge_num(x,0,n, arr) << " ";
    std::cout << find_first_ge_num(2*x,0,n, arr) << std::endl;
    return 0;
}