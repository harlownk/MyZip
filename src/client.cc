// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <sstream>
#include <climits>
#include <fstream>

#include "client.h"
#include "ByteInventory.h"
#include "HuffmanTree.h"

static const int arrSize = BI_NUM_ITEMS + 2;

int main(int argc, char** argv) {
  if (argc == 1) {
    // Print client help/usage
    PrintCommandHelp();
    exit(EXIT_SUCCESS);
  } else if (argc != 3) {
    // Make sure to update when dev continues.
    std::cerr << "Usage: ./client <mode> <filename>" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string *file_name = new std::string(argv[2]);
  if (std::string(argv[1]).compare("z") == 0) {  // Zip mode
    ZipFile(*file_name);
  } else if (std::string(argv[1]).compare("u") == 0) {  // Unzip mode
     UnzipFile(*file_name);
  } else {
    std::cerr << "mode " << argv[1] << " not recognized." << std::endl; 
  }

  delete file_name;
  exit(EXIT_SUCCESS);
}

static void PrintCommandHelp() {
    std::cout << "./client is used to compress text files." << std::endl;
}

static void ZipFile(std::string file_name) {
  std::cout << "Zipping " << file_name << "..." << std::endl;
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
    counts[arrSize - 2] = 1;   // This value is the EOF 'bytevalue'
    // TODO: Delimiter count MIGHT have an impact on the efficientcy.  
    counts[arrSize - 1] = 300;  // This is the value used as a delimiter 
    // Create the tree
    HuffmanTree tree(counts, arrSize);
    // Make translation lookup-table from tree
    std::unordered_map<int, std::string> *encodingMap = tree.getEncodings();
    // Encode the lookup-table into the file  Write it as a header?
    // for (auto it = encodingMap->begin(); it != encodingMap->end(); it++) {
    //   std::cout << (char) it->first << " " << it->second << std::endl;
    // }
    // TODO: Decide on a header layout and how to write it properly.
    // Read through file, writing new encoded file as we go.
    WriteZipFile(file_name, encodingMap);

    delete[] counts;
    delete encodingMap;
    std::cout << "Zip Successful." << std::endl;
}


static void UnzipFile(std::string file_name) {
  std::cout << "Unzipping " << file_name << std::endl;
      // Open file.
      // Parse translation lookup-table from header into memory
      // Read the encoded file translating and writing decoded file.
}

static int WriteZipFile(std::string origFileName, 
                        std::unordered_map<int, std::string> *map) {
  // Get the file names for both original and new file.
  char *prevFileName = new char[origFileName.size() + 1]();
  std::copy(origFileName.begin(), origFileName.end(), prevFileName);

  std::string extendedFileName = origFileName + ".mzip";
  char *zipFileName = new char[extendedFileName.size() + 1]();
  std::copy(extendedFileName.begin(), extendedFileName.end(), zipFileName);
  // Open the files for reading and writing.
  FILE *prevFile = fopen(prevFileName, "rb");
  FILE *zipFile = fopen(zipFileName, "wb");
  // Make a buffer for reading into.
  int8_t buffer[READ_BUFFER_SIZE];

  // Read through the whole file.
  int numRead = 0;
  std::string encodings("");
  while ((numRead = fread(&buffer, sizeof(int8_t), 1024, prevFile)) != 0) {
    // For each byte read:
    for (int i = 0; i < numRead; i++) {
      // Append the encoding:
      std::string currEncoding = map->at(buffer[i]);
      encodings += currEncoding;
    }
    int lastByteLen = encodings.size() % 8;
    // Save the excess for the next read round.
    std::string prevExcess(encodings.substr(encodings.size() - lastByteLen));
    encodings = encodings.substr(0, encodings.size() - lastByteLen);

    // Convert string encoding to bytes
    std::cout << encodings << std::endl;                                    // TESTING PRINTING
    WriteBitStringToFile(encodings, zipFile);
    encodings = prevExcess;
  }
  // Print excess and EOF sequence.
  encodings = encodings + map->at(arrSize - 2);
  WriteBitStringToFile(encodings, zipFile);


  delete[] prevFileName;
  delete[] zipFileName;
  fclose(prevFile);
  fclose(zipFile);
  return 1;
}

static void WriteBitStringToFile(std::string bitString, FILE *file) {
  int8_t buffer[READ_BUFFER_SIZE];
  // Convert the string encoding to bits to then be able to write.
  std::basic_stringstream<char> encodingStream(bitString);
  std::bitset<8> singleByte;
  uint count = 0;
  while(encodingStream >> singleByte) {
    buffer[count] = (uint8_t) singleByte.to_ulong();
    count++;
    if (count >= WRITE_BUFFER_SIZE) {
      if (fwrite(&buffer, sizeof(int8_t), count, file) != count) {
        std::cout << "Error occured a." << std::endl;
      }
      std::cout << "Error occured a." << std::endl;
      count = 0;
    }
  }
  if (fwrite(&buffer, sizeof(int8_t), count, file) != count) {
    std::cout << "Error occured a." << std::endl;
  }
}