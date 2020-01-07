// Copyright Nicholas Harlow

#ifndef SRC_HUFFMANTREE_H_
#define SRC_HUFFMANTREE_H_

#include <string>
#include <unordered_map>

namespace huffmanzipper {

class HuffmanTree {
 public:
  HuffmanTree() : root_(nullptr) { };  // TODO TEMPORARY UNTIL REAL DEVELOPED
  // Constructor that takes the array of the counts of bytes from a file
  // and makes a tree representing the possible encodings.
  HuffmanTree(int *counts, int size);

  HuffmanTree(std::unordered_map<int, std::string> *map);
  // Destructs the tree.
  ~HuffmanTree(); 

  // Returns a map that goes between ints and the string binary representation
  std::unordered_map<int, std::string> *getEncodings();
  

  // Node class that makes up the HuffmanTree 
  class HuffmanNode {
   public:
    // Creates a childless node with the givenn code and count.
    HuffmanNode(int code, int count);
    // Copy constructor.
    HuffmanNode(HuffmanNode &rightHandSide) = delete;
    // Cleans up the children of the node.
    ~HuffmanNode();
    // Implements lessthan comparison.
    int operator<(const HuffmanNode &other);
    // Assignment operator.
    // HuffmanNode &operator=(HuffmanNode &rightHandSide);

    // Fields:
    int byteCode_;
    int count_;
    HuffmanNode *left_;
    HuffmanNode *right_;
  };
  
  HuffmanNode *root_;
 private:
  void traverseEncodings(HuffmanNode *root, 
                         std::unordered_map<int, std::string> *map, 
                         std::string currEncoding);
  HuffmanNode *AddCodeToTree(HuffmanNode *root, std::string currEncoding, int code);
};

}  // namespace huffmanzipper

#endif  // SRC_HUFFMANTREE_H_