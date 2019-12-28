// Copyright Nicholas Harlow

#include <bitset>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <boost/crc.hpp>      // for boost::crc_basic, boost::crc_optimal

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

int32_t GetCRCOfFile(std::fstream &zipFile, std::streampos startOffset) {
  // Create the crc calculator.
  boost::crc_optimal<32, 0x1021, 0xFFFFFFFF, 0, false, false>  crc_ccitt;
  // Go to the start of file content.
  zipFile.seekp(startOffset);
  char currByte;
  while (!zipFile.eof()) {
    zipFile.read(&currByte, 1);  // This might be a potential slow down.
    crc_ccitt.process_byte(currByte);
  }
  zipFile.clear();  // need to clear the error flags that got set 
  return crc_ccitt.checksum();
}

uint64_t htonll(uint64_t x) {
  return ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFUL)) << 32) | 
          htonl((uint32_t)((x) >> 32)));
}

uint64_t ntohll(uint64_t x) {
  return ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFUL)) << 32) | 
          ntohl((uint32_t)((x) >> 32)));

}