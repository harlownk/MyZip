// Copyright Nicholas Harlow

#include <string>
#include <arpa/inet.h>        // For htonl(), etc.

#include "ZipperHeader.h"

#define ntohll(x) \
  ( ((uint64_t) (ntohl((uint32_t)((x << 32) >> 32))) << 32) |   \
    ntohl(((uint32_t)(x >> 32))) )
#define htonll(x) (ntohll(x))

namespace huffmanzipper {

std::string ZipperHeader::ToBitString() {
  // TODO: Implement
  return "";
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