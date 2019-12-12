// Copyright Nicholas Harlow

#ifndef SRC_HUFFMANZIPPER_H_
#define SRC_HUFFMANZIPPER_H_

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
  int WriteZipFileHeader(std::ofstream &zipFile,
                         std::streampos encodingsOffset, 
                         std::streampos bodyOffset);
  int WriteZipFileEncodings(std::ofstream &zipFile,
                            std::streampos offset, 
                            std::unordered_map<int, string> *map);
  int WriteZipFileBody(std::ofstream &zipFile,
                       std::streampos offset,
                       string origFileName,
                       std::unordered_map<int, string> *map);

  // Converts the bitstring to the corresponding bitstream that is then written
  // to the ofstream.  Will only write bitstrings that are of length % 8 == 0.  
  // Any bitstring provided that is not of that length, will have 0s padded to 
  // the end to be the proper length to write to a file.  It writes to the file
  // at the current streamposition set.
  // 
  // Returns -1 if there was an error writing, otherwise returns the number of 
  // bytes written.
  int WriteBitStringToFile(std::string bitString, std::ofstream &outfile);

  class ZipperHeader {
   public:
    ZipperHeader() { }
    ~ZipperHeader() { }

    // Creates a bit string from the current contents of the Header. The 
    // bit string's representation of each portion of the contents is in 
    // network order on disk.
    std::string ToBitString();
    void toHostFormat();
    void toNetworkFormat();

    // Fields:
    uint32_t magicCode_;
    uint32_t checkSum_;
    std::streampos encodingsOffset_;
    std::streampos bodyOffset_;
  };  // class ZipperHeader

  // Fields
  ZipperHeader header_;
};  // class HuffmanZipper

#endif  // SRC_HUFFMANZIPPER_H_