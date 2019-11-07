// Copyright Nicholas Harlow

#include <queue>

#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(int counts[], int size) {
  std::priority_queue<HuffmanNode *> queue;
  for (int i = 0; i < size; i++) {
    HuffmanNode *node = new HuffmanNode(i, counts[i]);
    queue.push(node);
  }
  while (size > 1) {
    HuffmanNode *nodefirst = queue.top();
    HuffmanNode *nodesecond = queue.top();
    int newSum = nodefirst->count_ + nodesecond->count_;
    HuffmanNode *newNode = new HuffmanNode(-1, newSum);
    newNode->children_[0] = nodefirst;
    newNode->children_[1] = nodesecond;
    queue.push(newNode);
  }
  root_ = queue.top();
}

HuffmanTree::~HuffmanTree() {
  delete root_;
}


// HuffmanNode declarations.
HuffmanTree::HuffmanNode::HuffmanNode(int code, int count) {
  byteCode_ = code;
  count_ = count;
  children_ = new HuffmanNode*[2];
}

HuffmanTree::HuffmanNode::~HuffmanNode() {
  delete[] children_;
}

int HuffmanTree::HuffmanNode::operator<(const HuffmanNode &other) {
  return other.count_ < count_;
}