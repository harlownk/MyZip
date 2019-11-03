// Copyright Nicholas Harlow

#include "ByteInventory.h"
#include <string>

ByteInventory::ByteInventory() {
  byteCounts_ = new int[NUM_ITEMS];
  size_ = NUM_ITEMS;
}

ByteInventory::ByteInventory(const ByteInventory &other) {
  byteCounts_ = new int[NUM_ITEMS];
  size_ = other.size_;
  for (int i = 0; i < size_; i++) {
    byteCounts_[i] = other.byteCounts_[i];
  }
}

ByteInventory::~ByteInventory() {
  delete[] byteCounts_;
}

ByteInventory &ByteInventory::addByte(int byte, int count=1) {
  return *this;
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

ByteInventory &ByteInventory::operator-=(const ByteInventory &decrement) {
  for (int i = 0; i < size_; i++) {
    byteCounts_[i] -= decrement.byteCounts_[i];
    if (byteCounts_[i] < 0) {
      byteCounts_[i] = 0;
    }
  }
  return *this;
}

std::string ByteInventory::toString() const {
  std::string result = std::string("[");
  for (int i = 0; i < size_ - 1; i++) {
    if (byteCounts_[i] != 0) {
      result = result + "'" + std::to_string(i) + "'=" + std::to_string(byteCounts_[i]) + ", ";
    }
  }
  return result + "'" + std::to_string(size_ - 1) + "'=" + std::to_string(byteCounts_[size_ - 1]) + "]";
}

ByteInventory operator+(const ByteInventory &first, 
                        const ByteInventory &second) {
  ByteInventory result = ByteInventory();
  result += first;
  result += second;
  return result;
}

ByteInventory operator-(const ByteInventory &first, 
                        const ByteInventory &second) {
  ByteInventory result = ByteInventory();
  result += first;
  result -= second;
  return result;
}