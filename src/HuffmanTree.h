// Copyright Nicholas Harlow

#ifndef SRC_HUFFMANTREE_H_
#define SRC_HUFFMANTREE_H_

#include <string>
#include <map>

// TODO: Finish the documentation for these 2 classes.  Include the 'dummy'
// values. Maybe push this to the client to add their desired values to
// the array before passing it in. This is probably the smarter idea.

class HuffmanTree {
 public:
  // Constructor that takes the array of the counts of bytes from a file
  // and makes a tree representing the possible encodings.
  HuffmanTree(int *counts, int size);
  // Destructs the tree.
  ~HuffmanTree(); 

  std::map<int, std::string> *getEncodings();
  

  // Node class that makes up the HuffmanTree 
  class HuffmanNode {
   public:
    HuffmanNode(int code, int count);
    ~HuffmanNode();
    int operator<(const HuffmanNode &other);

    // Fields:
    int byteCode_;
    int count_;
    HuffmanNode **children_;
  };
  HuffmanNode *root_;
 private:
  void traverseEncodings(HuffmanNode *root, 
                         std::map<int, std::string> *map, 
                         std::string currEncoding);
};

#endif  // SRC_HUFFMANTREE_H_