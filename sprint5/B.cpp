#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

struct TreeInfo {
    bool is_balanced;
    int depth;
};

TreeInfo dfs(const Node* root) {
    TreeInfo return_value;

    if (root == nullptr) {
        return_value.is_balanced = true;
        return_value.depth = 0;

    } else {
        auto left  = dfs(root->left);
        auto right = dfs(root->right);

        return_value.is_balanced = (left.is_balanced && right.is_balanced 
                                    && (abs(left.depth - right.depth) <= 1));
        return_value.depth = 1 + std::max({left.depth, right.depth});
    }

    return return_value;
}

bool Solution(const Node* root) {
    auto tree_info = dfs(root);
    return tree_info.is_balanced;
} 


#ifndef REMOTE_JUDGE
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});    
    Node node4({10, nullptr, nullptr});
    Node node5({2, &node3, &node4});
    assert(Solution(&node5));
}

int main() {
  test();
}
#endif