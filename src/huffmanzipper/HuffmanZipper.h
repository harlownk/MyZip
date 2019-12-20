// Copyright Nicholas Harlow

#ifndef SRC_HUFFMANZIPPER_H_
#define SRC_HUFFMANZIPPER_H_

#define WRITE_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 1024

#include <string>
#include <unordered_map>

#include "ZipperHeader.h"

namespace huffmanzipper {

// TODO Docs!!!!

class HuffmanZipper {
 public:
  HuffmanZipper() { }
  ~HuffmanZipper() { }
  bool ZipFile(std::string file_name);
  bool UnzipFile(std::string file_name);
  
 private:
  int WriteZipFileHeader(std::fstream &zipFile,
                         uint32_t checkSum,
                         std::streampos encodingsOffset, 
                         std::streampos bodyOffset);
  int WriteZipFileEncodings(std::fstream &zipFile,
                            std::streampos offset, 
                            std::unordered_map<int, std::string> *map);
  int WriteZipFileBody(std::fstream &zipFile,
                       std::streampos offset,
                       std::string origFileName,
                       std::unordered_map<int, std::string> *map);

  // Converts the bitstring to the corresponding bitstream that is then written
  // to the ofstream.  Will only write bitstrings that are of length % 8 == 0.  
  // Any bitstring provided that is not of that length, will have 0s padded to 
  // the end to be the proper length to write to a file.  It writes to the file
  // at the current streamposition set.
  // 
  // Returns -1 if there was an error writing, otherwise returns the number of 
  // bytes written.
  int WriteBitStringToFile(std::string bitString, std::fstream &outfile);
  // Fields
  ZipperHeader header_;

};  // class HuffmanZipper

}

#endif  // SRC_HUFFMANZIPPER_H_