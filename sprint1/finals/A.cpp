//accepted parcel ID: 80155881

//idea:
//  arr input -> {O(2N)} -> arr left_null_dist, right_nill_dist -> 
//  -> {O(N)} -> arr null_dist = min(left_null_dist, right_null_dist) = out.

//code:

#include <iostream>
#include <vector>
#include <algorithm>

template <class IteratorType>
void UniDirectNullDistTransform(IteratorType pbegin, IteratorType pend) { //modifies the input!
    int n = pend - pbegin;
    int dist_cnt = n + 1; //infinity

    for (auto p = pbegin; p != pend; ++p) {
        if (*p == 0) {
            dist_cnt = 0;
        }
        *p = dist_cnt;
        dist_cnt++;
    }

    return;
}

std::vector<int> GetElementwiseMin(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    int n = arr1.size();
    std::vector<int> min_arr(n);
    
    for (int i = 0; i < n; ++i) {
        min_arr[i] = std::min(arr1[i], arr2[i]);
    }

    return min_arr;
}

std::vector<int> GetNullDist(const std::vector<int>& arr) {
    auto left_null_dist = arr;
    UniDirectNullDistTransform(left_null_dist.begin(), left_null_dist.end());

    auto right_null_dist = arr;
    UniDirectNullDistTransform(right_null_dist.rbegin(), right_null_dist.rend());

    auto null_dist = GetElementwiseMin(left_null_dist, right_null_dist);

    return null_dist;
}

void print(const std::vector<int>& arr) {
    for (int x : arr) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}

int main() {
    int n;

    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    print(GetNullDist(arr));
    return 0;
}
