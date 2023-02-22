// Input: array of 1 and 0 (e.g. 011101001010010100) of size n
// Output: length of the biggest balanced contageous subarray i.e. with the same
// number of zeros and ones 
// Complexity: O(n)
//

#include <iostream>
#include <vector>
#include <unordered_map>

int readNum();
std::vector<int> readArr(int n);
void printArr(const std::vector<int> &arr);

int findMaxBalancedSubRangeLength(const std::vector<int> &arr);

int main() {
    auto n = readNum();
    auto arr = readArr(n);
    std::cout << findMaxBalancedSubRangeLength(arr) << std::endl;
    return 0;
}


// The algorithm is two pass as follows.
// w.l.o.g. say we have a range [begin, end) of {-1, 1}.
// At first pass we construct two maps:
//  cumsum: "index" i -> sum of [begin, i)
//  greatest_last: "sum" x -> the greatest index s.t. cumsum(index) == x
// At the second pass we go through all indices considering them as a possible 
// "first" of the desired subrange. The maximum subrange with such "first" is 
// described as:
//  [first, greatest_last[cum_sum[first]])                          (1)*
// Throughout the pass we get the lengths of this ranges and choose the greatest 
// one.
//
// *The statement (1) is to be proved.
// _________proof outline:____________
// Suppose we have got a range [begin, end) of {-1,1}
//  say last >= first,
//  if
//      \sum([begin, first)) == x
//      \sum([begin, last)) == x
//  then
//      \sum([first, last)) == 0
//
//  in reverse, for any first,
//  if 
//      \sum([begin, first)) == x,
//  then for all last >= first
//      \sum([first, last)) == 0 iff \sum([begin, last)) == x
//  from here the statement follows easily.
// ___________________________________
//  

int findMaxBalancedSubRangeLength(const std::vector<int> &arr) {
    int n = arr.size();
    std::unordered_map<int, int> greatest_last;
    std::unordered_map<int, int> cumsum;

    cumsum[0] = 0;
    greatest_last[0] = 0;
    for (int i = 0; i < n; ++i) {
        cumsum[i+1] = cumsum[i] + ((arr[i] == 1) ? 1 : -1);
        greatest_last[cumsum[i+1]] = i+1;
    }

    int max_length = 0;
    for (int first = 0; first < n; ++first) {
        int last = greatest_last[cumsum[first]];
        if ((last - first) > max_length) {
            max_length = last - first;
        }
    }

    return max_length;
}

//____IO_functions____
int readNum() {
    int x;
    std::cin >> x;
    std::cin.ignore();
    return x;
}

std::vector<int> readArr(int n) {
    std::vector<int> arr(n);
    for (auto &x : arr) {
        std::cin >> x;
    }
    std::cin.ignore();
    return arr;
}

void printArr(const std::vector<int> &arr) {
    for (const auto &x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return;
}