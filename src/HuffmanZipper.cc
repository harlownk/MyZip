// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <sstream>
#include <climits>
#include <fstream>

#include "HuffmanZipper.h"
#include "ByteInventory.h"
#include "HuffmanTree.h"

using std::string;

static const int arrSize = BI_NUM_ITEMS + 2;
static const int delimiterVal = arrSize - 1;
static const int eofVal = arrSize - 2;

static const int32_t magicWord = 0xc0defade;
static const string zipFileEnding = ".mzip";


bool HuffmanZipper::ZipFile(string file_name) {
  // Open file.
  std::ifstream currfile;
  currfile.open(file_name, std::ios::in | std::ios::binary);
  if (!currfile.is_open()) {
    std::cerr << "Error encountered while opening " << file_name << std::endl;
    exit(EXIT_FAILURE);
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
  // TODO: Delimiter count MIGHT have an impact on the efficientcy.  
  counts[delimiterVal] = 300;  // This is the value used as a delimiter 
  // Create the trees
  HuffmanTree tree(counts, arrSize);
  // Make translation lookup-table from tree
  std::unordered_map<int, string> *encodingMap = tree.getEncodings();

  std::streampos currOffset = 0;  // Should be the total size of the header.
  // TODO: Check if this file opens correctly (error handle etc.)
  std::ofstream zipFile(file_name + zipFileEnding, std::ios_base::binary);
  // Write the encoding map to the zipfile.
  // TODO: Implement writing the encoding map.
  // currOffset += WriteZipFileEncodings(, zipFile, );
  // Write the body of the zipfile.
  WriteZipFileBody(zipFile, currOffset, file_name, encodingMap);
  // TODO: Implememnt writing of the header.
  // WriteZipFileHeader(, zipFile, );

  delete[] counts;
  delete encodingMap;
  return true;
}

bool HuffmanZipper::UnzipFile(string file_name) {
  std::cout << "Unzipping " << file_name << std::endl;
  // TODO Implement
  // Open file.
  // Check header and file integrity.
  // Parse translation lookup-table from header into memory
  // Read the encoded file translating and writing decoded file.
  return false;
}

int HuffmanZipper::WriteZipFileHeader(std::ofstream &zipFile,
                                      std::streampos encodingsOffset, 
                                      std::streampos bodyOffset) {
  // TODO Implement
  return 0;
}

int HuffmanZipper::WriteZipFileEncodings(std::ofstream &zipFile,
                                         std::streampos offset, 
                                         std::unordered_map<int, string> *map) {
  // TODO Implement
  return 0;
}

int HuffmanZipper::WriteZipFileBody(std::ofstream &zipFile, 
                                    std::streampos offset,
                                    string origFileName, 
                                    std::unordered_map<int, string> *map) {
  // TODO Check if this file opens correctly.
  // Open the file to write to.
  std::ifstream oldFile(origFileName, std::ios_base::binary);
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
                                         std::ofstream &outfile) {
  // Pad the bitString out to multiple of 8 so we can write full bytes.
  int bitStringOverhang = bitString.size() % 8;
  for (int i = 0; i < 8 - bitStringOverhang; i++) {
    bitString += "0";
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

std::string HuffmanZipper::ZipperHeader::ToBitString() {
  // TODO: Implement
  return "";
}