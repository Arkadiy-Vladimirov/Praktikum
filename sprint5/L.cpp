#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

#include <algorithm>

int siftDown(std::vector<int>& heap, int idx) {
    if (2*idx == (heap.size()-1)) { // one child 
        if (heap[idx] < heap[2*idx]) {
            std::swap(heap[idx], heap[2*idx]);
            return siftDown(heap, 2*idx);
        }
    }
    if (2*idx < (heap.size()-1)) { // two children
        auto max_it = std::max_element(heap.begin() + 2*idx, heap.begin() + 2*idx + 2);
        int max_idx = std::distance(heap.begin(), max_it);

        if (heap[idx] < heap[max_idx]) {
            std::swap(heap[idx], heap[max_idx]);
            return siftDown(heap, max_idx);
        }
    }
    // no chlidren or no swaps
    return idx;
}

#ifndef REMOTE_JUDGE
void test() {
    std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
    assert(siftDown(sample, 2) == 5);
}


int main() {
    test();
}
#endif