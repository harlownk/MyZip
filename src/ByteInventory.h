// Copyright Nicholas Harlow

#define NUM_ITEMS 258

class ByteInventory {
 public:
  // Creates a ByteInventory with full counts of 0. 
  ByteInventory();
  // Copies the current ByteInventory.
  ByteInventory(ByteInventory &other);
  // Cleans up the ByteInventory.
  ~ByteInventory();
  // Overridden assignment operator.  
  ByteInventory &operator=(ByteInventory &other);
 private:
  int *byteCounts_;
  int size_;
};