// Copyright Nicholas Harlow

#ifndef SRC_ZIPPERHEADER_H_
#define SRC_ZIPPERHEADER_H_

#include <string>
#include <iostream>

namespace huffmanzipper {

class ZipperHeader {
 public:
  ZipperHeader() { }
  ~ZipperHeader() { }

  // Creates a bit string from the current contents of the Header. The 
  // bit string's representation of each portion of the contents is in 
  // network order on disk.
  std::string ToBitString();
  void ToHostFormat();
  void ToDiskFormat();

  // Fields:
  uint32_t magicCode_;
  uint32_t checkSum_;
  std::streampos encodingsOffset_;
  std::streampos bodyOffset_;
 private:
  std::string FieldToBitString(uint32_t field);
  std::string FieldToBitString(int64_t field);
};  // class ZipperHeader

const int kHeaderLength = sizeof(ZipperHeader);

}  // namespace huffmanzipper

#endif  // SRC_ZIPPERHEADER_H_