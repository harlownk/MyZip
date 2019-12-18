// Copyright Nicholas Harlow

#include <string>
#include <bitset>
#include <arpa/inet.h>        // For htonl(), etc.

#include "ZipperHeader.h"

#define ntohll(x) \
  ( ((uint64_t) (ntohl((uint32_t)((x << 32) >> 32))) << 32) |   \
    ntohl(((uint32_t)(x >> 32))) )
#define htonll(x) (ntohll(x))

namespace huffmanzipper {

std::string ZipperHeader::ToBitString() {
  std::string result("");
  result += FieldToBitString(magicCode_);
  result += FieldToBitString(checkSum_);
  result += FieldToBitString(encodingsOffset_);
  result += FieldToBitString(bodyOffset_);
  return result;
}

void ZipperHeader::ToHostFormat() {
  magicCode_ = ntohl(magicCode_);
  checkSum_ = ntohl(checkSum_);
  encodingsOffset_ = ntohll(encodingsOffset_);
  bodyOffset_ = ntohll(bodyOffset_);
}

void ZipperHeader::ToDiskFormat() {
  magicCode_ = htonl(magicCode_);
  checkSum_ = htonl(checkSum_);
  encodingsOffset_ = htonll(encodingsOffset_);
  bodyOffset_ = htonll(bodyOffset_);
}

std::string ZipperHeader::FieldToBitString(uint32_t field) {
  std::bitset<32> fieldBitSet(field);
  return fieldBitSet.to_string();
}

std::string ZipperHeader::FieldToBitString(int64_t field) {
  std::bitset<64> fieldBitSet(field);
  return fieldBitSet.to_string();
}


}  // namespace huffmanzipper