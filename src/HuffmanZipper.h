// Copyright Nicholas Harlow

#ifndef SRC_HUFFMANZIPPER_H_
#define SRC_HUFFMANZIPPER_H_

#define ZIP_HEADER_LENGTH 32
#define WRITE_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 1024

#include <string>
#include <unordered_map>

using std::string;

class HuffmanZipper {
 public:
  HuffmanZipper() { }
  ~HuffmanZipper() { }
  bool ZipFile(string file_name);
  bool UnzipFile(string file_name);
 private:
  int WriteZipFileBody(string origFileName, 
                       std::ofstream &zipFile, 
                       std::unordered_map<int, string> *map);

  // Converts the bitstring to the corresponding bitstream that is then written
  // to the ofstream.  Will only write bitstrings that are of length % 8 == 0.  
  // Any bitstring provided that is not of that length, will have 0s padded to the
  // end to be the proper length to write to a file.
  // 
  // Returns false if there is any error writing to the file, otherwise returns
  // true.
  bool WriteBitStringToFile(std::string bitString, std::ofstream &outfile);
};

#endif  // SRC_HUFFMANZIPPER_H_