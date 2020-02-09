// Copyright Nicholas Harlow

#include <queue>
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
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
  currDecodeNode_ = root_;
}

HuffmanTree::HuffmanTree(std::unordered_map<int, std::string> *map) : root_(nullptr) {
  for (auto iter = map->begin(); iter != map->end(); iter++) {
    int currCode = (*iter).first;
    std::string encoding = (*iter).second;
    root_ = AddCodeToTree(root_, encoding, currCode);
  }
  currDecodeNode_ = root_;
}

HuffmanTree::~HuffmanTree() {
  if (root_) {
    delete root_;
  }
}


std::unordered_map<int, std::string> *HuffmanTree::getEncodings() {
  auto *encodingMap = new std::unordered_map<int, std::string>;
  traverseEncodings(root_, encodingMap, "");
  return encodingMap;
}

std::vector<int> HuffmanTree::DecodeBitString(const std::string bitString) {
  std::vector<int> resultVector;
  for (auto iter = bitString.begin(); iter != bitString.end(); iter++) {
    char currChar = *iter;
    if (currChar == '0') {
      currDecodeNode_ = currDecodeNode_->left_;
    } else if (currChar == '1') {
      currDecodeNode_ = currDecodeNode_->right_;
    }
    
    if (currDecodeNode_ == nullptr) {
      resultVector.push_back(-1);
      currDecodeNode_ = root_;
    } else if (currDecodeNode_->byteCode_ != -1) {
      resultVector.push_back(currDecodeNode_->byteCode_);
      currDecodeNode_ = root_;  
    }
  }

  return resultVector;
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

HuffmanTree::HuffmanNode 
*HuffmanTree::AddCodeToTree(HuffmanTree::HuffmanNode *root, std::string currEncoding, int code) {
  if (currEncoding.size() == 0) {
    // We reached the end
    root = new HuffmanNode(code, 0);
    return root;
  } else if (root == NULL) {
    // We need to add a node to the tree, set the code to an arbitrary
    // value to denote a non ending node.
    // Make the count/frequency a nonsense value since it doesnt matter 
    // for this type of tree.
    root = new HuffmanNode(-1, 0);
  }

  if (currEncoding.at(0) == '0') {
    root->left_ = AddCodeToTree(root->left_, currEncoding.substr(1), code);
  } else {
    root->right_ = AddCodeToTree(root->right_, currEncoding.substr(1), code);
  }
  return root;
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

// HuffmanTree::HuffmanNode 
// &HuffmanTree::HuffmanNode::operator=(HuffmanTree::HuffmanNode &rightHandSide) {
//   *this = rightHandSide;
// }

}  // namespace huffmanzipper