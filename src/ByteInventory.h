// Copyright Nicholas Harlow

#define NUM_ITEMS 258

// ByteInventory that contains a count of each byte.
class ByteInventory {
 public:
  // Constructers etc:
  // Creates a ByteInventory with full counts of 0. 
  ByteInventory();
  // Copies the current ByteInventory.
  ByteInventory(const ByteInventory &other);
  // Cleans up the ByteInventory.
  ~ByteInventory();

  // Operators:
  // Overridden assignment operator.  
  ByteInventory &operator=(const ByteInventory &other);

  // Increment operator
  ByteInventory operator+=(const ByteInventory &increment);

  // Decrement operator
  ByteInventory operator-=(const ByteInventory &increment);

 private:
  int *byteCounts_;
  int size_;
};

ByteInventory operator+(const ByteInventory &first, 
                        const ByteInventory &second);

ByteInventory operator-(const ByteInventory &first, 
                        const ByteInventory &second);