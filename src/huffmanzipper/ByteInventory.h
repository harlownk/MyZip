// Copyright Nicholas Harlow

#ifndef SRC_BYTEINVENTORY_H_
#define SRC_BYTEINVENTORY_H_

#include <string>
#include <cstdint>

#define BI_NUM_ITEMS 256

namespace huffmanzipper {
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

  // Add a new item to the inventory. If the byte is invalid there is no effect.
  void addByte(uint16_t byte, int count=1);

  // Gets the count of the given byte in the inventory. Returns -1 if the byte
  // is invalid.
  int getCount(int byte) const;

  // Operators:
  // Overridden assignment operator.  
  ByteInventory &operator=(const ByteInventory &other);

  // Increment operator
  ByteInventory &operator+=(const ByteInventory &increment);


  // toString, printing a list of the byte values and the associated counts
  // if the count is > 0.
  std::string toString() const;

 private:
  int *byteCounts_;
  int size_;
};

ByteInventory operator+(const ByteInventory &first, 
                        const ByteInventory &second);


} // namespace huffmanzipper

#endif  // SRC_BYTEINVENTORY_H_