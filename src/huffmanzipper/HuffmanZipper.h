// Copyright Nicholas Harlow

#ifndef SRC_HUFFMANZIPPER_H_
#define SRC_HUFFMANZIPPER_H_

#define WRITE_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 1024

#include <string>
#include <unordered_map>

#include "ZipperHeader.h"
#include "HuffmanTree.h"

// TODO Docs
namespace huffmanzipper {

class HuffmanZipper {
 public:
  HuffmanZipper() { }
  ~HuffmanZipper() { }
  bool ZipFile(std::string file_name);
  bool ZipFile(std::string filePath, std::string destinationPath);
  bool UnzipFile(std::string file_name);
  bool UnzipFile(std::string filePath, std::string destinationPath);
  
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
  
  ZipperHeader ReadZipFileHeader(std::ifstream &encodedFile, 
                                 std::streampos offset);

  // Returns a HuffmanTree pointer, passing responsibility of the allocated 
  // memory to the caller.
  HuffmanTree *ReadZipFileEncodings(std::ifstream &encodedFile,
                                    std::streampos encodingOffset,
                                    int encodingsLength);

  // Reads from the encoded/zipped file starting at the given offset, decodes 
  // the file byte-by-byte using the given HuffmanTree, and then writing 
  // the output through the file provided.
  void DecodeZipFileBody(std::ifstream &zippedFile, 
                         std::ofstream &outFile, 
                         std::streampos bodyOffset, 
                         HuffmanTree *decodingTree);


  // Converts the bitstring to the corresponding bitstream that is then written
  // to the ofstream.  Will only write bitstrings that are of length % 8 == 0.  
  // Any bitstring provided that is not of that length, will have 0s padded to 
  // the end to be the proper length to write to a file.  It writes to the file
  // at the current streamposition set.
  // 
  // Returns -1 if there was an error writing, otherwise returns the number of 
  // bytes written.
  int WriteBitStringToFile(std::string bitString, std::fstream &outfile);

  std::string ReadBitStringFromFile(std::ifstream &file, 
                                    std::streampos start, 
                                    int numBytes);
};  // class HuffmanZipper

}

#endif  // SRC_HUFFMANZIPPER_H_