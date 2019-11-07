// Copyright Nicholas Harlow

class HuffmanTree {
 public:
  HuffmanTree(const ByteInventory &inventory) {

  }
 private:
  class HuffmanNode {
   public:
    int count_;
    int byteCode_;
    HuffmanNode *children_[2];
  };
  HuffmanNode *root;
};