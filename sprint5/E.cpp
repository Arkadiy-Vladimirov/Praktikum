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

using namespace std;

#include <limits>
const int MINUS_INFTY = std::numeric_limits<int>::min();
const int PLUS_INFTY  = std::numeric_limits<int>::max();

bool is_sorted(const Node* node, int left_bound = MINUS_INFTY,
                                 int right_bound = PLUS_INFTY) {
  if (node == nullptr) {
    return true;
  }
  if ((left_bound < node->value) && (node->value < right_bound)) {
    return is_sorted(node->left , left_bound , node->value) 
        && is_sorted(node->right, node->value, right_bound);
  } else {
    return false;
  }
} 

bool Solution(const Node* root) {
    return is_sorted(root);
} 


#ifndef REMOTE_JUDGE
void test() {
    {
      Node node1({1, nullptr, nullptr});
      Node node2({4, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(Solution(&node5));
    }
    {
      Node node1({1, nullptr, nullptr});
      Node node2({5, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(!Solution(&node5));
    }
}


int main() {
  test();
}
#endif