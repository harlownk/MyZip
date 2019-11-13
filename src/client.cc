// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>
#include <climits>
#include <fstream>

#include "client.h"
#include "ByteInventory.h"
#include "HuffmanTree.h"

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
    int arrSize = BI_NUM_ITEMS + 2;
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

static int WriteZipFile(std::string orig_file_name, 
                        std::unordered_map<int, std::string> *map) {
  std::ofstream newFile();
  WriteZipHeader();
  WriteZipBody();
  return 1;
}

static int WriteZipHeader() {
  return 1;
}

static int WriteZipBody() {
  return 1;
}