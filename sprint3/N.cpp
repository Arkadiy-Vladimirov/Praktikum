// merge intersecting segements and sort in ascenging order

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

std::vector<std::pair<int,int>> read_arr(int n);
void print_arr(std::vector<std::pair<int,int>> arr);

bool cmp_left(std::pair<int,int> segment_a, std::pair<int,int> segment_b) {
    return (segment_a.first < segment_b.first);
}

std::vector<std::pair<int,int>> uniting_sort(std::vector<std::pair<int,int>> segments);

int main() {
    int n;
    std::cin >> n;
    auto segments = read_arr(n);
    auto sorted_segments = uniting_sort(segments);
    print_arr(sorted_segments);
    return 0;
}


// The idea of the algorithm is to go through an array of segments sorted with 
// respect to left boundary value, while merging what intersects.
//
// We consider the first segment as a pivot, - an initial guess of the resulting
// merged segment that would contain the pivot. The left boundary would stay 
// unchanged (as there is nothing less).
// Than we go through all the segments with left bound inside our inital guess,
// updating the right bound each time we find a segment with the right end out 
// of our guess.
// After the pass we would collect all the segments that merge and stop at the 
// first segment that does not intersect with any of the previous. This would be
// the new pivot.

std::vector<std::pair<int,int>> uniting_sort(std::vector<std::pair<int,int>> segments) {
    //sort wrt left boundary
    std::sort(segments.begin(), segments.end(), cmp_left);
    
    //merge intersecting segments
    std::vector<std::pair<int,int>> merged_segments;

    auto pivot_it = segments.begin();
    while (pivot_it != segments.end()) { // pivots loop
        int left_bound  = (*pivot_it).first;
        int right_bound = (*pivot_it).second;
        auto segment_it = pivot_it + 1;
        while (segment_it != segments.end() && ((*segment_it).first <= right_bound)) { // merging loop
            if ((*segment_it).second > right_bound) {
                right_bound = (*segment_it).second;
            }
            segment_it++;
        }
        merged_segments.push_back(std::pair<int,int> (left_bound, right_bound));
        pivot_it = segment_it;
    }
    return merged_segments;
}

std::vector<std::pair<int, int>> read_arr(int n) { 
    std::vector<std::pair<int, int>> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i].first >> arr[i].second;
    }
    return arr;
}

void print_arr(std::vector<std::pair<int, int>> arr) {
    for (auto pair : arr) {
        std::cout << pair.first <<  " " << pair.second << std::endl;
    }
    return;
}