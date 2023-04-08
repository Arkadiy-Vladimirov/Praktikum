#ifndef REMOTE_JUDGE
struct Node {  
  Node* left;  
  Node* right;
  int value;
  int size;
};
#endif

#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>
#include <utility>

int getSize(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

std::pair<Node*, Node*> split(Node* root, int k) {
    if (root == nullptr) {
        return std::make_pair(nullptr, nullptr);
    }

    if (getSize(root->left) >= k) { // if left subtree contains k nodes already
        auto [left_split, right_split] = split(root->left, k);
        root->left = right_split;
        root->size = getSize(root->left) + getSize(root->right) + 1;
        return std::make_pair(left_split, root);
    } else {                        // otherwise
        auto [left_split, right_split] = split(root->right, k - 1 - getSize(root->left));
        root->right = left_split;
        root->size = getSize(root->left) + getSize(root->right) + 1;
        return std::make_pair(root, right_split);
    }
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 3, 1});
    Node node2({nullptr, &node1, 2, 2});
    Node node3({nullptr, nullptr, 8, 1});
    Node node4({nullptr, nullptr, 11, 1});
    Node node5({&node3, &node4, 10, 3});
    Node node6({&node2, &node5, 5, 6});
    std::pair<Node*, Node*> res = split(&node6, 4);
    assert(res.first->size == 4);
    assert(res.second->size == 2);
}


int main() {
  test();
}
#endif