// Copyright Nicholas Harlow

#include "ByteInventory.h"

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

ByteInventory &ByteInventory::operator=(const ByteInventory &other) {
  size_ = other.size_;
  for (int i = 0; i < size_; i++) {
    byteCounts_[i] = other.byteCounts_[i];
  }
  return *this;
}

ByteInventory ByteInventory::operator+=(const ByteInventory &increment) {
  return ByteInventory();
}

ByteInventory ByteInventory::operator-=(const ByteInventory &increment) {
  return ByteInventory();
}

ByteInventory operator+(const ByteInventory &first, 
                        const ByteInventory &second) {
  return ByteInventory();
}

ByteInventory operator-(const ByteInventory &first, 
                        const ByteInventory &second) {
  return ByteInventory();
}