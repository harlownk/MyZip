// Copyright Nicholas Harlow

#include <unordered_map>
#include <list>
#include <arpa/inet.h>        // For htonl(), etc.
#include <cstdint>

#include "ZipperEncodings.h"
#include "Util.h"

namespace huffmanzipper {

ZipperEncodings::ZipperEncodings(const std::unordered_map<int, std::string> &map) {
  for (auto iter = map.begin(); iter != map.end(); iter++) {
    // Get the information from the encoding map
    int currCode = (*iter).first;
    std::string currString = (*iter).second;
    int16_t stringLen = currString.size();
    // Create the stucture that contains information about each encoding.
    EncodingInfo currInfo;
    currInfo.code_ = currCode;
    currInfo.encodingSizeBits_ = stringLen;
    // Prepend onto each encoding enough 0s to fill out a full byte to make 
    // it easier to read back. 
    if (stringLen % 8 != 0) {
      int stringByteLen = (stringLen / 8) + 1;
      int paddingNeeded = (stringByteLen * 8) - stringLen;  // Subtract stringLen from bitLen needed.
      std::string padding("");
      for (int i = 0; i < paddingNeeded; i++) {
        padding += "0";
      }
      currString = padding + currString;
    }
    currInfo.encoding_ = currString;
    // Push the structure onto the end of the list.
    allEncodingInfo_.push_back(currInfo);
  }
  size_ = allEncodingInfo_.size();
}

ZipperEncodings::ZipperEncodings(const std::string paramBitString) {
  std::string bitString = paramBitString;
  std::string sizeBitString = bitString.substr(0, sizeof(int32_t) * 8);
  bitString = bitString.substr(sizeof(int32_t) * 8);
  size_ = std::bitset<32>(sizeBitString).to_ulong();
  int listSize = ntohl(size_);

  // Build the list.
  for (int i = 0; i < listSize; i++) {
    EncodingInfo currInfo;
    // Get the code bits from the bit string.
    std::string codeBitString = bitString.substr(0, sizeof(currInfo.code_) * 8);
    bitString = bitString.substr(sizeof(currInfo.code_) * 8);
    currInfo.code_ = std::bitset<32>(codeBitString).to_ulong();
    // Get the bitLengthBits bits from the bit string.
    std::string bitLengthBitString = bitString.substr(0, sizeof(currInfo.encodingSizeBits_) * 8);
    bitLengthBitString = bitString.substr(sizeof(currInfo.encodingSizeBits_) * 8);
    currInfo.encodingSizeBits_ = std::bitset<32>(codeBitString).to_ulong();

    // Convert to Host format, then use the size to trim the encoding stream.
    currInfo.ToHostFormat();
    int excessSizeBits;
    int readSize;
    if ((excessSizeBits = 8 - (currInfo.encodingSizeBits_ % 8)) != 8) {
      readSize = currInfo.encodingSizeBits_ + excessSizeBits;
    } else {
      readSize = currInfo.encodingSizeBits_;
    }
    currInfo.encoding_ = bitString.substr(0, readSize);
    int excess = readSize - currInfo.encodingSizeBits_;
    currInfo.encoding_ = currInfo.encoding_.substr(excess);
    currInfo.ToDiskFormat();

    // Add to list.
    allEncodingInfo_.push_back(currInfo);
  }
}

// Passes ownership of the map to the caller.
std::unordered_map<int, std::string> *ZipperEncodings::GetEncodingMap() {
  std::unordered_map<int, std::string> *result = new std::unordered_map<int, std::string>;
  for (auto iter = allEncodingInfo_.begin(); iter != allEncodingInfo_.end(); iter++) {
    EncodingInfo currEncoding = *iter;
    result->insert({currEncoding.code_, currEncoding.encoding_});
  }
  return result;
}

std::string ZipperEncodings::ToBitString() {
  std::string result("");
  result += FieldToBitString((uint32_t) size_);
  for (auto iter = allEncodingInfo_.begin(); iter != allEncodingInfo_.end(); iter++) {
    EncodingInfo currInfo = *iter;
    result += currInfo.ToBitString();
  }
  return result;
}

void ZipperEncodings::ToHostFormat() {
  size_ = ntohl(size_);
  for (auto iter = allEncodingInfo_.begin(); iter != allEncodingInfo_.end(); iter++) {
    EncodingInfo currInfo = *iter;
    currInfo.ToHostFormat();
  }
}

void ZipperEncodings::ToDiskFormat() {
  size_ = htonl(size_);
  for (auto iter = allEncodingInfo_.begin(); iter != allEncodingInfo_.end(); iter++) {
    EncodingInfo currInfo = *iter;
    currInfo.ToDiskFormat();
  }
}


// EncodingInfo method declarations
std::string ZipperEncodings::EncodingInfo::ToBitString() {
  std::string result("");
  result += FieldToBitString((uint32_t) code_);
  result += FieldToBitString((uint16_t) encodingSizeBits_);
  result += encoding_;
  return result;
}

void ZipperEncodings::EncodingInfo::ToHostFormat() {
  code_ = ntohl(code_);
  encodingSizeBits_ = ntohs(encodingSizeBits_);
}

void ZipperEncodings::EncodingInfo::ToDiskFormat() {
  code_ = htonl(code_);
  encodingSizeBits_ = htons(encodingSizeBits_);
}


}  // namespace huffmanzipper