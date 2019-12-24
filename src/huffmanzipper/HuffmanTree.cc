// Copyright Nicholas Harlow

#include <queue>
#include <string>
#include <unordered_map>
#include <iostream>
#include <cstdlib>

#include "HuffmanTree.h"


namespace huffmanzipper {

HuffmanTree::HuffmanTree(int *counts, int size) : root_(nullptr) {
  auto cmp = [](HuffmanNode *left, HuffmanNode *right) { return *left < *right; };
  std::priority_queue<HuffmanNode *, 
                      std::vector<HuffmanNode *>, 
                      decltype(cmp)>  queue(cmp);
  for (int i = 0; i < size; i++) {
    if (counts[i] > 0) {
      HuffmanNode *node = new HuffmanNode(i, counts[i]);
      queue.push(node); 
    }
  }
  while (queue.size() > 1) {
    HuffmanNode *nodefirst = queue.top();
    queue.pop();
    HuffmanNode *nodesecond = queue.top();
    queue.pop();
    int newSum = nodefirst->count_ + nodesecond->count_;
    HuffmanNode *newNode = new HuffmanNode(-1, newSum);
    newNode->left_ = nodefirst;
    newNode->right_ = nodesecond;
    queue.push(newNode);
  }
  root_ = queue.top();
}

HuffmanTree::HuffmanTree(std::unordered_map<int, std::string> *map) {
  // AddCodeToTree(currCode, encoding);
}

HuffmanTree::~HuffmanTree() {
  delete root_;
}

std::unordered_map<int, std::string> *HuffmanTree::getEncodings() {
  auto *encodingMap = new std::unordered_map<int, std::string>;
  traverseEncodings(root_, encodingMap, "");
  return encodingMap;
}

void HuffmanTree::traverseEncodings(HuffmanNode *root, 
                                    std::unordered_map<int, std::string> *map, 
                                    std::string currEncoding) {
  if (root->byteCode_ != -1) {
    map->insert(std::pair<int, std::string>(root->byteCode_, currEncoding));
  } else {
    traverseEncodings(root->left_, map, currEncoding + "0");
    traverseEncodings(root->right_, map, currEncoding + "1");
  }
}

// HuffmanNode declarations.
HuffmanTree::HuffmanNode::HuffmanNode(int code, int count) {
  byteCode_ = code;
  count_ = count;
  left_ = nullptr;
  right_ = nullptr;
}

HuffmanTree::HuffmanNode::~HuffmanNode() {
  if (left_) {
    delete left_;
  }
  if (right_) {
    delete right_;
  }
  
}

int HuffmanTree::HuffmanNode::operator<(const HuffmanNode &other) {
  return other.count_ < count_;
}

}  // namespace huffmanzipper