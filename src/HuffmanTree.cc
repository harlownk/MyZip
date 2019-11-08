// Copyright Nicholas Harlow

#include <queue>
#include <string>
#include <map>
#include <iostream>
#include <cstdlib>

#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(int counts[], int size) {
  auto cmp = [](HuffmanNode *left, HuffmanNode *right) { return left->count_ > right->count_; };
  std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, decltype(cmp)> queue(cmp);
  for (int i = 0; i < size; i++) {
    if (counts[i] > 0) {
      HuffmanNode *node = new HuffmanNode(i, counts[i]);
      queue.push(node);
    }
  }
  // add the other items like a seperator item, and an EOF character representation?
  while (queue.size() > 1) {
    HuffmanNode *nodefirst = queue.top();
    queue.pop();
    HuffmanNode *nodesecond = queue.top();
    queue.pop();
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

std::map<int, std::string> *HuffmanTree::getEncodings() {
  std::map<int, std::string> *encodingMap = new std::map<int, std::string>;
  traverseEncodings(root_, encodingMap, "");
  return encodingMap;
}

void HuffmanTree::traverseEncodings(HuffmanNode *root, 
                                    std::map<int, std::string> *map, 
                                    std::string currEncoding) {
  if (root->byteCode_ != -1) {
    // std::cout << std::to_string(root->byteCode_) << std::endl;
    std::cout << currEncoding << std::endl;
    map->insert(std::pair<int, std::string>(root->byteCode_, currEncoding));
  } else {
    traverseEncodings(root->children_[0], map, currEncoding + std::to_string(0));
    traverseEncodings(root->children_[1], map, currEncoding + std::to_string(1));
  }
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