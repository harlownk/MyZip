// Copyright Nicholas Harlow

#include <string>
#include <bitset>
#include <cstdint>

#include "ZipperHeader.h"
#include "Util.h"

namespace huffmanzipper {

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