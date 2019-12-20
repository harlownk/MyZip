// Copyright Nicholas Harlow

#include "Util.h"

namespace huffmanzipper {

std::string FieldToBitString(uint16_t field) {
  std::bitset<16> fieldBitSet(field);
  return fieldBitSet.to_string();
}

std::string FieldToBitString(uint32_t field) {
  std::bitset<32> fieldBitSet(field);
  return fieldBitSet.to_string();
}

std::string FieldToBitString(uint64_t field) {
  std::bitset<64> fieldBitSet(field);
  return fieldBitSet.to_string();
}

}