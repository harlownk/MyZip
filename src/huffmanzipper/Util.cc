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

}