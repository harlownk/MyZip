// Copright Nicholas Harlow

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <arpa/inet.h>        // For htonl(), etc.
#include <boost/crc.hpp>      // for boost::crc_basic, boost::crc_optimal
#include <bitset>
#include <iostream>

namespace huffmanzipper {
// Represents Utility functions and macros etc that the Zipper uses
// across its various classes.

// Macros to change the endianess of 64bit data types.
// Changes from network order (big endian) to host order (little endian)
#define ntohll(x) \
  ( ((uint64_t) (ntohl((uint32_t)((x << 32) >> 32))) << 32) |   \
    ntohl(((uint32_t)(x >> 32))) )
#define htonll(x) (ntohll(x))

// Creates a bit-string from a 16bit data type, takes the data type
// as an argument and returns a string with length 16, that shows the bit
// representation of the data type.
std::string FieldToBitString(uint16_t field);

// Creates a bit-string from a 32bit data type, takes the data type
// as an argument and returns a string with length 32, that shows the bit
// representation of the data type.
std::string FieldToBitString(uint32_t field);

// Creates a bit-string from a 64bit data type, takes the data type
// as an argument and returns a string with length 64, that shows the bit
// representation of the data type.
std::string FieldToBitString(uint64_t field);

// Takes the zipFile and calculates the CRC of the file starting at the 
// byte at startOffset until the end of the file.
int32_t GetCRCOfFile(std::fstream &zipFile, std::streampos startOffset);

}  // namespace huffmanzipper

#endif  //SRC_UTIL_H_