// Copyright Nicholas Harlow

#ifndef SRC_ZIPPERHEADER_H_
#define SRC_ZIPPERHEADER_H_

#include <string>
#include <iostream>

// TODO Add all the documentation for the class and the methods etc.

namespace huffmanzipper {

class ZipperHeader {
 public:
  ZipperHeader() { }
  ZipperHeader(std::string bitString);
  ~ZipperHeader() { }


  // Creates a bit string from the current contents of the Header. The 
  // bit string's representation of each portion of the contents is in 
  // network order on disk.
  std::string ToBitString();
  void ToHostFormat();
  void ToDiskFormat();

  // Fields:
  uint64_t encodingsOffset_;
  uint64_t bodyOffset_;
  uint32_t magicCode_;
  uint32_t checkSum_;
};  // class ZipperHeader

}  // namespace huffmanzipper

#endif  // SRC_ZIPPERHEADER_H_