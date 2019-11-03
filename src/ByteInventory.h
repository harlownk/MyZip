// Copyright Nicholas Harlow

#include <string>

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

  // Add a new item to the inventory.
  ByteInventory &addByte(int byte, int count);

  // Operators:
  // Overridden assignment operator.  
  ByteInventory &operator=(const ByteInventory &other);

  // Increment operator
  ByteInventory &operator+=(const ByteInventory &increment);

  // Decrement operator
  ByteInventory &operator-=(const ByteInventory &increment);

  // toString, printing a list of the byte values and the associated counts
  // if the count is > 0.
  std::string toString() const;

 private:
  int *byteCounts_;
  int size_;
};

ByteInventory operator+(const ByteInventory &first, 
                        const ByteInventory &second);

ByteInventory operator-(const ByteInventory &first, 
                        const ByteInventory &second);