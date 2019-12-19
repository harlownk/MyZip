// Copyright Nicholas Harlow

#ifndef SRC_ZIPPERENCODINGS_H_
#define SRC_ZIPPERENCODINGS_H_

#include <string>
#include <unordered_map>

namespace huffmanzipper {

class ZipperEncodings {
 public:
  ZipperEncodings(std::unordered_map *map);
  ~ZipperEncodings();

  std::string ToBitString();
  void ToHostFormat();
  void ToDiskFormat();

  // Fields

 private:
  // TODO Need a dynamic buffer to read into or out of somehow? Constructor that 
  // takes an array and processes it or something?
}  // class ZipperEncodings

}  // namespace huffmanzipper


#endif  // SRC_ZIPPERENCODINGS_H_