// Copyright Nicholas Harlow

class HuffmanTree {
 public:
  HuffmanTree(int counts[], int size);
  ~HuffmanTree(); 
 public:
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
};