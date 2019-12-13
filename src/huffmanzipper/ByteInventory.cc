// Copyright Nicholas Harlow

#include "ByteInventory.h"
#include <string>

namespace huffmanzipper {

ByteInventory::ByteInventory() {
  byteCounts_ = new int[BI_NUM_ITEMS];
  size_ = BI_NUM_ITEMS;
  for (int i = 0; i < size_; i++) {
    byteCounts_[i] = 0;
  }
}

ByteInventory::ByteInventory(const ByteInventory &other) {
  byteCounts_ = new int[BI_NUM_ITEMS];
  size_ = other.size_;
  for (int i = 0; i < size_; i++) {
    byteCounts_[i] = other.byteCounts_[i];
  }
}

ByteInventory::~ByteInventory() {
  delete[] byteCounts_;
}

void ByteInventory::addByte(int byte, int count) {
  if (byte > size_) {
    return;
  }
  byteCounts_[byte] += count;
}

int ByteInventory::getCount(int byte) const {
  if (byte >= size_) {
    return -1;
  }
  return byteCounts_[byte];
}

ByteInventory &ByteInventory::operator=(const ByteInventory &other) {
  size_ = other.size_;
  for (int i = 0; i < size_; i++) {
    byteCounts_[i] = other.byteCounts_[i];
  }
  return *this;
}

ByteInventory &ByteInventory::operator+=(const ByteInventory &increment) {
  for (int i = 0; i < size_; i++) {
    byteCounts_[i] += increment.byteCounts_[i];
  }
  return *this;
}

std::string ByteInventory::toString() const {
  std::string result = std::string("[");
  for (int i = 0; i < size_; i++) {
    if (byteCounts_[i] != 0) {
      result = result + "'" + std::to_string(i) + "'=" + 
               std::to_string(byteCounts_[i]) + ", ";
    }
  }
  if (result.back() == ' ') {
    result.pop_back();
    result.pop_back();
  }
  return result + "]";
}

ByteInventory operator+(const ByteInventory &first, 
                        const ByteInventory &second) {
  ByteInventory result = ByteInventory();
  result += first;
  result += second;
  return result;
}

}  // namespace huffmanzipper