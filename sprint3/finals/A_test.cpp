// accepted parcel ID: ---
//
// Input: a corrupted (shifted) sorted array(n) with all unique elements
// Output: the position of required element x (O(log n))
//
// Algorithm: 
// The algorithm operates recursively. Base of the recurion is an empty array -- 
// nothing is found in this case. At each other iteration the following steps 
// are performed:
//  - the array is splitted into parts [0, n/2), [n/2, n): in a shifted sorted
//   array we have only one monotonicity violation point which falls into one 
//   of the segments. Thus, the other one is sorted. (see fig.1)
//
//                      |=|
//                   |=||=|
//                |=||=||=|
//                |=||=||=|                     |=|
//                |=||=||=|                  |=||=|
//                |=||=||=|               |=||=||=|
//                |=||=||=|            |=||=||=||=|
//                |=||=||=|         |=||=||=||=||=|
//                |=||=||=|   |=|   |=||=||=||=||=|
//                |=||=||=||=||=|   |=||=||=||=||=|
//                 0  1  2  3  4     5  6  7  8  9 
//                            (fig. 1)
//    "array splits into sorted part [5, 10) and corrupted part [0, 5)"
//
// - To determine whether a subarray is sorted we only need to check its 
//  bounds: the subarray is sorted iff left_bound <= right_bound. (Worth to 
//  mention: it works only as long as all elements are unique.)
// - As the type of each segment is determined we check if x may lie inside the 
//  sorted one: this holds iff left_bound <= x <= right_bound. If so the result 
//  of the algorithm is the result of standard bin search over the segment.
// - Otherwise, x may only lie in the corrupted segment and we perform the 
//  algorithm over it, falling to the next level of the recursion. 
//
// Complexity:
// Regardless of the branch of the algorithm (the main one, or bin search), at 
// each step the data size is divided by two until it reaches zero and the 
// process stops. Hence, log n iterations are performed. 
// At each step O(1) operations are done and O(1) of memory space is used.
// Thus, both time and space complexity of the algorithm are O(log n).
//

#include <iostream>
#include <vector>
#include <algorithm>

int broken_search(const std::vector<int>& vec, int k); // wrapper for corrupted_search

template <class ForwardIt, class T>
ForwardIt corrupted_search(ForwardIt first, ForwardIt last, const T& value);

template <class ForwardIt> inline
std::tuple<ForwardIt, ForwardIt, ForwardIt, ForwardIt> determine_partition(
                                                ForwardIt first, ForwardIt last
                                                ); 


std::vector<int> readArr(int n);
int readNum();

int main() {
    int n = readNum();
    int x = readNum();
    auto arr = readArr(n);
    std::cout << broken_search(arr, x) << std::endl;
    return 0;
}



template <class ForwardIt, class T>
ForwardIt corrupted_search(ForwardIt first, ForwardIt last, const T& value) {
    if (first == last) { //if the range is empty
        return last;     //return "not found"
    }

    //the range is either
    //[first, last) = [corrupted_first, corrupted_last) + [sorted_first, sorted_last)
    //or 
    //[first, last) = [sorted_first, sorted_last) + [corrupted_first, corrupted_last)
    ForwardIt sorted_first, sorted_last, corrupted_first, corrupted_last;
    std::tie(sorted_first, sorted_last, corrupted_first, corrupted_last) = 
                                            determine_partition(first, last);
    //note: sorted range is always non-empty 

    ForwardIt found_it;
    //now the value is either in the sorted part or in the corrupted one
    if ((*sorted_first <= value) && (value <= *(sorted_last-1))) { 
        //in sorted range we use standart bin_search
        found_it = std::lower_bound(sorted_first, sorted_last, value);
        //value is either inside sorted range either nowhere already
        if (*found_it != value) {
            found_it = last;
        }
    } else {
        found_it = corrupted_search(corrupted_first, corrupted_last, value);
        if (found_it == corrupted_last) {
            found_it = last;
        }
    }

    return found_it;
}


template <class ForwardIt> inline
std::tuple<ForwardIt, ForwardIt, ForwardIt, ForwardIt> determine_partition(
                                            ForwardIt first, ForwardIt last) {
    // [first, last) = [first, middle) + [middle, last)
    ForwardIt middle = first + (last - first)/2;

    ForwardIt sorted_first, sorted_last;
    ForwardIt corrupted_first, corrupted_last;

    if (*middle <= *(last-1)) {
    // [first, last) = [corrupted_first, corrupted_last) + [sorted_first, sorted_last)
        sorted_first    = middle; sorted_last    = last;
        corrupted_first = first ; corrupted_last = middle;
    } else {
    // [first, last) = [sorted_first, sorted_last) + [corrupted_first, corrupted_last)
        sorted_first    = first; sorted_last    = middle;
        corrupted_first = middle ; corrupted_last = last;
    }

    return std::make_tuple( sorted_first,
                            sorted_last, 
                            corrupted_first, 
                            corrupted_last);
}

int broken_search(const std::vector<int>& vec, int k) {
    auto found_iter = corrupted_search(vec.cbegin(), vec.cend(), k);

    if (found_iter != vec.cend()) {
        return (found_iter - vec.cbegin());
    } else {
        return -1;
    }
}

std::vector<int> readArr(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    return arr;
}

int readNum() {
    int x;
    std::cin >> x;
    return x;
}