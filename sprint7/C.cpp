#include <iostream>
#include <vector>
#include <algorithm>

struct Pile {
    int cost; // per unit volume
    int vol;  // total volume
};

bool operator < (const Pile &lhs, const Pile &rhs) {
    if (lhs.cost < rhs.cost) {
        return true;
    }
    if (lhs.cost > rhs.cost) {
        return false;
    }
    if (lhs.vol < rhs.vol) {
        return true;
    }
    if (lhs.vol > rhs.vol) {
        return false;
    }
    return false;
}

int main() {
    int cap; //capacity
    std::cin >> cap;

    int n;
    std::cin >> n;

    std::vector<Pile> piles(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> piles[i].cost >> piles[i].vol;
    }

    std::sort(piles.rbegin(), piles.rend());

    long long profit = 0;
    for (int i = 0; (i < n) && (cap != 0); ++i) {
        long long take =  std::min(piles[i].vol, cap);
        profit += take*piles[i].cost;
        cap -= take;
    }

    std::cout << profit << std::endl;

    return 0;
}