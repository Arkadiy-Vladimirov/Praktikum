#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

#include <algorithm>

int siftUp(std::vector<int>& heap, int idx) {
    if (idx == 1) {
        return 1;
    }
    if (heap[idx/2] < heap[idx]) {
        std::swap(heap[idx/2], heap[idx]);
        return siftUp(heap, idx/2);
    }
    return idx;
}

#ifndef REMOTE_JUDGE
void test() {
    std::vector<int> sample = {-1, 12, 6, 8, 3, 15, 7};
    assert(siftUp(sample, 5) == 1);
}


int main() {
    test();
}
#endif