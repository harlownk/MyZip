// Copright Nicholas Harlow

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <arpa/inet.h>        // For htonl(), etc.
#include <bitset>
#include <iostream>

namespace huffmanzipper {

#define ntohll(x) \
  ( ((uint64_t) (ntohl((uint32_t)((x << 32) >> 32))) << 32) |   \
    ntohl(((uint32_t)(x >> 32))) )
#define htonll(x) (ntohll(x))

std::string FieldToBitString(uint16_t field);
std::string FieldToBitString(uint32_t field);
std::string FieldToBitString(uint64_t field);

}  // namespace huffmanzipper

#endif  //SRC_UTIL_H_