// Copyright Nicholas Harlow

#ifndef SRC_ZIPPERENCODINGS_H_
#define SRC_ZIPPERENCODINGS_H_

#include <string>
#include <unordered_map>
#include <list>

namespace huffmanzipper {

// ZipperEncodings is representeded when on disc in the following form:
//            +-----------------------------------+
//            |  'count' of different encodings   | 
//            |       4 bytes                     |
//            +-----------------------------------+
//            |   List of EncodingInfo structs    |
//            |     that is 'count' long          | 
//            |                                   |
//            +-----------------------------------+ 
//
//                EncodingInfo structs 
//            +-----------------------------------+
//            |                                   | 
//            |                                   |
//            |                                   |
//            |                                   |
//            |       // TODO: Documentation                           |
//            |                                   |
//            +-----------------------------------+
//
// 

class ZipperEncodings {
 public:
  ZipperEncodings(const std::unordered_map<int, std::string> &map);
  // ~ZipperEncodings();

  // Creates an entire bitstring that is writable.
  std::string ToBitString();
  // Converts all of the contained EncodingInfos to hostformat, able to be 
  // read and used.
  void ToHostFormat();
  // Converts all of the contained EncodingInfos to disk format able to be 
  // written.
  void ToDiskFormat();

  // Fields

 private: 
  // TODO: make this more clear?
  // Represents a disk writable/readable struct containing the information 
  // about an encoding.  Contains the int/char code that the encoding will 
  // represent. The encoding is prepended with 0s to fill up the byte, 
  // and the bit length tells how many bits of the given bytes are part of the
  // encoding. Then the encoding as a string is present, the length of the string
  // represents full bytes (string.size() % 8 == 0 to be valid and writable).
  class EncodingInfo {
   public:
    // Gives a bitstring representation of the encoding info struct.
    std::string ToBitString();
    // Converts the encoding info to the proper format for the host computer to use
    void ToHostFormat();
    // Converts the encoding info to the proper format to write to disk so it is usable
    // regardless of platform byte ordering.
    void ToDiskFormat();
    
    // Fields
    // Represents the character code or other code used in the encoding (ex: EOF is >255)
    int32_t code_;
    // The size of the encoding this struct points too
    int16_t encodingSizeBits_;
    // The actual encoding represented as a string.  must be string.size() % 8 == 0
    // to be a valid encoding to write.
    std::string encoding_;
  };  // class EncodingsInfo

  // Fields:
  std::list<EncodingInfo> allEncodingInfo_;
};  // class ZipperEncodings

}  // namespace huffmanzipper
#endif  // SRC_ZIPPERENCODINGS_H_