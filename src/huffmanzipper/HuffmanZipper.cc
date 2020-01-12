// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <sstream>
#include <climits>
#include <fstream>
#include <cstdint>

#include "HuffmanZipper.h"
#include "ZipperHeader.h"
#include "ZipperEncodings.h"
#include "ByteInventory.h"
#include "HuffmanTree.h"
#include "Util.h"

using std::string;

namespace huffmanzipper {

// Classwide constants: 
static const int arrSize = BI_NUM_ITEMS + 1;
static const int eofVal = arrSize - 1;

static const int32_t magicWord = 0xc0defade;
static const string zipFileEnding = ".mzip";

bool HuffmanZipper::ZipFile(string file_name) {
  // Open file that will be zipped.
  std::ifstream currfile;
  currfile.open(file_name, std::ios::in | std::ios::binary);
  if (!currfile.is_open()) {  // Make sure the file actually openned.
    std::cerr << "Error encountered while opening " << file_name << std::endl;
    return false;
  }
  // Make a byte inventory of the file.
  // Read everything, counting each byte as we go in this ByteInventory.
  ByteInventory bi;
  currfile >> std::noskipws;
  char currval;
  while (currfile >> currval) {
    bi.addByte(currval);
  }
  currfile.close();

  // Make an encoding tree:
  // Convert BI into an array.
  int *counts = new int[BI_NUM_ITEMS + 2];
  for (int i = 0; i < arrSize - 2; i++) {
    counts[i] = bi.getCount(i);
  }
  counts[eofVal] = 1;   // This value is the EOF 'bytevalue'
  // Create the trees
  HuffmanTree tree(counts, arrSize);
  // Make translation lookup-table from tree
  std::unordered_map<int, string> *encodingMap = tree.getEncodings();

  std::fstream zipFile(file_name + zipFileEnding,  
                       std::ios::in | std::ios::out | 
                       std::ios_base::binary | std::ios_base::trunc);
  if (!zipFile.is_open()) {  // Make sure the zip file opens w/o error.
    std::cerr << "Error encountered while creating " << 
                  file_name + zipFileEnding << std::endl;
    delete[] counts;
    delete encodingMap;
    return false;
  }
  
  // Write everything after the header first. Move cursor to after the header.
  std::streampos currOffset = sizeof(ZipperHeader);

  // Write the encoding map to the zipfile.
  currOffset += WriteZipFileEncodings(zipFile, currOffset, encodingMap);
  // Write the body of the zipfile.  Encode the actual file using the
  // encodings from the tree.
  int bodyLen = WriteZipFileBody(zipFile, currOffset, file_name, encodingMap);
  if (bodyLen == -1) {
    std::cerr << "Error encountered while opening file to zip: " << 
                 file_name << std::endl;
    delete[] counts;
    delete encodingMap;
    return false;
  }
  // Need to calculate the checksum to pass to the header to write.
  int32_t crcVal = GetCRCOfFile(zipFile, sizeof(ZipperHeader));
  WriteZipFileHeader(zipFile, crcVal, sizeof(ZipperHeader), currOffset);

  // Clean up
  delete[] counts;
  delete encodingMap;
  return true;
}

bool HuffmanZipper::UnzipFile(string file_name) {
  std::cout << "Unzipping " << file_name << std::endl;
  // TODO Implement
  // Open file.
  std::ifstream zippedFile(file_name);
  // Get the header of the zip file.
  ZipperHeader header = ReadZipFileHeader(zippedFile, 0);
  // Check header and file integrity.  header returned in host format.
  // TODO Check magicword, and crc of the file, make sure they are correct.
  // if (header.magicCode_ != magicWord) {
  //   return false;
  // }
  // int32_t fileCRC = CRCGetCRCOfFile();
  // Parse translation lookup-table from header into memory
  int encodingsLength = header.bodyOffset_ - header.encodingsOffset_;
  HuffmanTree *encodingTree = ReadZipFileEncodings(zippedFile, 
                                                  header.encodingsOffset_, 
                                                  encodingsLength);
  // Read the encoded file translating and writing decoded file.
  // DecodeZipFileBody(zippedFile, header.bodyOffset_, encodingTree);

  delete encodingTree;
  return false;
}

int HuffmanZipper::WriteZipFileHeader(std::fstream &zipFile,
                                      uint32_t checkSum,
                                      std::streampos encodingsOffset, 
                                      std::streampos bodyOffset) {
  // Build the header.
  ZipperHeader header;
  header.magicCode_ = magicWord;
  header.checkSum_ = checkSum;
  header.encodingsOffset_ = encodingsOffset;
  header.bodyOffset_ = bodyOffset;
  // Convert to proper format.
  header.ToDiskFormat();

  // Convert to string and print to the file at proper location:
  std::string headerBitString = header.ToBitString();
  zipFile.seekp(0);  // Write at head of file.
  return WriteBitStringToFile(headerBitString, zipFile);
}

int HuffmanZipper::WriteZipFileEncodings(std::fstream &zipFile,
                                         std::streampos offset, 
                                         std::unordered_map<int, string> *map) {
  
  std::string bitString;
  ZipperEncodings encodings(*map);
  encodings.ToDiskFormat();
  
  bitString = encodings.ToBitString();
  zipFile.seekp(offset);  // Move to the right position before writing.
  int count = WriteBitStringToFile(bitString, zipFile);
  return count;
}

int HuffmanZipper::WriteZipFileBody(std::fstream &zipFile, 
                                    std::streampos offset,
                                    string origFileName, 
                                    std::unordered_map<int, string> *map) {
  // Open the file to read from that is going to be zipped.
  std::ifstream oldFile(origFileName, std::ios_base::binary);
  if (!oldFile.is_open()) {  // File couldnt open correctly.
    return -1;
  }
  zipFile.seekp(offset);

  // Read through the whole file.
  int currChar = 0;
  string encodingBuffer("");
  while (oldFile.good()) {
    currChar = oldFile.get();
    if (currChar == -1) {
      break;
    }
    string currCharEncoded(""); 
    try {
      currCharEncoded = map->at(currChar);
    } catch (const std::out_of_range &e) {
      std::cerr << "Error: Can't find encoding." << std::endl;
      return -1;
    }
    encodingBuffer += currCharEncoded;
    if (encodingBuffer.size() > WRITE_BUFFER_SIZE * 8) {
      // Filled the buffer, write to file.
      // Trim down to a multiple of 8 for bytelength.
      int excessCount = encodingBuffer.size() % 8;
      string excess = encodingBuffer.substr(encodingBuffer.size() - excessCount);
      encodingBuffer = 
                  encodingBuffer.substr(0, encodingBuffer.size() - excessCount);
      WriteBitStringToFile(encodingBuffer, zipFile);
      // Save excess.
      encodingBuffer = excess;
    }
  }  // Whole file read and encoded.  Any excess needs writen to the file.
  string eofCode = map->at(eofVal);
  encodingBuffer += eofCode;
  WriteBitStringToFile(encodingBuffer, zipFile);
  return 1;
}

int HuffmanZipper::WriteBitStringToFile(std::string bitString, 
                                         std::fstream &outfile) {
  // Pad the bitString out to multiple of 8 so we can write full bytes.
  int bitStringOverhang = bitString.size() % 8;
  if (bitStringOverhang != 0) {
    for (int i = 0; i < 8 - bitStringOverhang; i++) {
      bitString += "0";
    }
  }

  char *buffer = new char[(bitString.size() / 8) + 1];
  // Convert the string encoding to bits to then be able to write.
  std::basic_stringstream<char> encodingStream(bitString);
  std::bitset<8> singleByte;

  uint count = 0;
  while (encodingStream >> singleByte) {
    // There is some error with the stream at this point.
    if (!encodingStream.good()) {
      return -1;
    }
    buffer[count] = (uint8_t) singleByte.to_ulong();
    count++;
  }
  outfile.write(buffer, count);

  delete[] buffer;
  return count;
}

ZipperHeader HuffmanZipper::ReadZipFileHeader(std::ifstream &encodedFile, 
                                              std::streampos offset) {
  int bytes = sizeof(ZipperHeader);
  std::string headerBitString = ReadBitStringFromFile(encodedFile, offset, bytes);
  ZipperHeader header(headerBitString);
  header.ToHostFormat();
  return header;
}

HuffmanTree *HuffmanZipper::ReadZipFileEncodings(std::ifstream &encodedFile,
                                                 std::streampos encodingOffset,
                                                 int encodingsLength) {
  // Create a ZipperEncodings that we can read and parse.
  std::string encodingsBitString = ReadBitStringFromFile(encodedFile, 
                                                         encodingOffset,
                                                         encodingsLength);
  ZipperEncodings allEncodings(encodingsBitString);
  allEncodings.ToHostFormat();
  // Get the map from the encodings.
  std::unordered_map<int, std::string> *encodingMap = allEncodings.GetEncodingMap();
  // Make a tree out of the encodings.
  HuffmanTree *decodingTree = new HuffmanTree(encodingMap);

  delete encodingMap;
  return decodingTree;
}

std::string HuffmanZipper::ReadBitStringFromFile(std::ifstream &file, 
                                                 std::streampos start, 
                                                 int numBytes) {
  std::string result("");
  file.seekg(start);
  char currChar;
  int end = ((int) start) + numBytes;
  for (int i = start; i < end; i++) {
    currChar = file.get();
    std::bitset<8> currBits(currChar);
    result += currBits.to_string();
  }
  return result;
}

}  // namespace huffmanzipper