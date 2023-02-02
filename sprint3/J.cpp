//prints tracing of bubble sort algorithm

#include <iostream>
#include <vector>
#include <algorithm>

void read_arr(std::vector<int> &arr);
void print_arr(std::vector<int> &arr);
void trace_bubble_sort(std::vector<int> &arr);

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    read_arr(arr);

    if (std::is_sorted(arr.begin(), arr.end())) {
        print_arr(arr);
    } else {
        trace_bubble_sort(arr);
    }

    return 0;
}



void trace_bubble_sort(std::vector<int> &arr) {
    int n = arr.size();
    bool sorted = false;

    for (int i = 0; i < n; ++i) {
        sorted = true;
        for (int j = 0; j < (n-i-1); ++j) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                sorted = false;
            }
        }

        if (!sorted) {
            print_arr(arr);
        } else {
            break;
        }
    } 
    
    return;
}

void read_arr(std::vector<int> &arr){
    for (auto &element : arr) {
        std::cin >> element;
    }
    return;
}

void print_arr(std::vector<int> &arr) {
    for (auto element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    return;
}

