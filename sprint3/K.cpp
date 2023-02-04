#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using Iterator = std::vector<int>::iterator;
using CIterator = std::vector<int>::const_iterator;

/*void print_arr(Iterator begin, Iterator end) {
    for (Iterator it = begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}*/

std::vector<int> merge(
	CIterator left_begin, CIterator left_end, 
	CIterator right_begin, CIterator right_end) {

    std::vector<int> merged_arr;
    auto left = left_begin;
    auto right = right_begin;

    while ((left != left_end) && (right != right_end)) {
        if (*left < *right) {
            merged_arr.push_back(*left);
            left++;
        } else {
            merged_arr.push_back(*right);
            right++;
        }
    }

    while (left != left_end) {
        merged_arr.push_back(*left);
        left++;
    }
    while (right < right_end) {
        merged_arr.push_back(*right);
        right++;
    }
	
    return merged_arr;
}

void merge_sort(Iterator begin, Iterator end) {
    if ((end - begin) <= 1) {
        return; //is sorted already
    }

    auto mid = begin + (end - begin)/2;
    merge_sort(begin, mid); 
    merge_sort(mid, end);
    auto sorted_arr = merge(begin, mid,  mid, end);
    std::copy(sorted_arr.begin(), sorted_arr.end(), begin);
	return;
}

void test_merge_sort() {
	std::vector<int> a = {1, 4, 9};
	std::vector<int> b = {2, 10, 11};
	std::vector<int> c = merge(a.cbegin(), a.cend(), b.cbegin(), b.cend());
	std::vector<int> expected = {1, 2, 4, 9, 10, 11};
	assert(c == expected);
	std::vector<int> d = {1, 4, 2, 10, 1, 2};
	std::vector<int> sorted = {1, 1, 2, 2, 4, 10};
	merge_sort(d.begin(), d.end());
	assert(d == sorted);
}