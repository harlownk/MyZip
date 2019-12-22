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
}

std::string ZipperEncodings::ToBitString() {
  std::string result("");
  for (auto iter = allEncodingInfo_.begin(); iter != allEncodingInfo_.end(); iter++) {
    EncodingInfo currInfo = *iter;
    result += currInfo.ToBitString();
  }
  return result;
}

void ZipperEncodings::ToHostFormat() {
  for (auto iter = allEncodingInfo_.begin(); iter != allEncodingInfo_.end(); iter++) {
    EncodingInfo currInfo = *iter;
    currInfo.ToHostFormat();
  }
}

void ZipperEncodings::ToDiskFormat() {
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