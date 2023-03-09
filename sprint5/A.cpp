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
#include <limits>
const int MINUS_INFTY = std::numeric_limits<int>::min();

int Solution(const Node* root) {
  if (root == nullptr) {
    return MINUS_INFTY;
  }
  return std::max({Solution(root->left), 
                            root->value, 
                   Solution(root->right)
                  });
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({2, &node3, nullptr});
    assert(Solution(&node4) == 3);
} 

int main() {
  test();
}
#endif