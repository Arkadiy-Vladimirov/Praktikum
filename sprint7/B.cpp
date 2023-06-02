#include <iostream>
#include <vector>
#include <algorithm>

typedef double Time;

struct Interval {
    Time start;
    Time finish;
};

bool operator < (const Interval &lhs, const Interval &rhs) {
    if (lhs.finish < rhs.finish) {
        return true;
    } 
    //if ((lhs.finish == rhs.finish) && (rhs.start == rhs.finish)) {
    //    return true; // "could be an option" given the problem description but 
                       // implies x < x for some x and hence is not a strict 
                       // ordering (w.) (moreover, implies x != x for some x)
    //}
    if (lhs.finish > rhs.finish) {
        return false;
    }
    if (lhs.start < rhs.start) {
        return true;
    }
    if (lhs.start > rhs.start) {
        return false;
    }
    
    return false;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Interval> intervals(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> intervals[i].start >> intervals[i].finish;
    }

    std::sort(intervals.begin(), intervals.end());

    std::vector<Interval> schedule;
    Time cur_fin = 0.0;
    int int_cnt = 0;
    for (const auto &inter : intervals) {
        if (inter.start >= cur_fin) {
            schedule.push_back(inter);
            cur_fin = inter.finish;
            int_cnt++;
        }
    }

    std::cout << int_cnt << std::endl;
    for (const auto &inter : schedule) {
        std::cout << inter.start << " " << inter.finish << std::endl;
    }
    return 0;
}