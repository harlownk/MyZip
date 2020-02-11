// Copyright Nicholas Harlow

#include <string>
#include <bitset>
#include <cstdint>

#include "ZipperHeader.h"
#include "../util/Util.h"

using util::FieldToBitString;
using util::ntohll;
using util::htonll;

namespace huffmanzipper {

ZipperHeader::ZipperHeader(std::string bitString) {
  // Parse the bitstring and initialize the  header.
  std::string magicCodeString = bitString.substr(0, sizeof(magicCode_) * 8);
  bitString = bitString.substr(sizeof(magicCode_) * 8);
  std::string checkSumString = bitString.substr(0, sizeof(checkSum_) * 8);
  bitString = bitString.substr(sizeof(checkSum_) * 8);
  std::string encodingOffsetString = bitString.substr(0, sizeof(encodingsOffset_) * 8);
  bitString = bitString.substr(sizeof(encodingsOffset_) * 8);
  std::string bodyOffsetString = bitString.substr(0, sizeof(bodyOffset_) * 8);

  magicCode_ = std::bitset<32>(magicCodeString).to_ulong();
  checkSum_ = std::bitset<32>(checkSumString).to_ulong();
  encodingsOffset_ = std::bitset<64>(encodingOffsetString).to_ulong();
  bodyOffset_ = std::bitset<64>(bodyOffsetString).to_ulong();
}

std::string ZipperHeader::ToBitString() {
  std::string result("");
  result += FieldToBitString(magicCode_);
  result += FieldToBitString(checkSum_);
  result += FieldToBitString((uint64_t) encodingsOffset_);
  result += FieldToBitString((uint64_t) bodyOffset_);
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

}  // namespace huffmanzipper