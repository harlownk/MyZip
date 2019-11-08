// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>
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
  std::string file_name = argv[2];
  if (std::string(argv[1]).compare("z") == 0) {  // Zip mode
    std::cout << "Zipping " << file_name << std::endl;
    // Open file.
    std::ifstream currfile;
    currfile.open(file_name, std::ios::in | std::ios::binary);
    if (!currfile.is_open()) {
      std::cerr << "Error encountered while opening " << file_name << std::endl;
      return EXIT_FAILURE;
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
    int arrSize = BI_NUM_ITEMS;
    int *counts = new int[BI_NUM_ITEMS];
    for (int i = 0; i < arrSize; i++) {
      counts[i] = bi.getCount(i);
    }
    // Create the tree
    HuffmanTree tree(counts, arrSize);
    // Make translation lookup-table from tree
    tree.getEncodings();
    // Encode the lookup-table into the file
    // Read through file, writing new encoded file as we go.
  } else if (std::string(argv[1]).compare("u") == 0) {  // Unzip mode
    std::cout << "Unzipping " << file_name << std::endl;
    // Open file.
    // Parse translation lookup-table from header into memory
    // Read the encoded file translating and writing decoded file. 
  } else {
    std::cerr << "mode " << argv[1] << " not recognized." << std::endl; 
  }
  exit(EXIT_SUCCESS);
}

static void PrintCommandHelp() {
    std::cout << "./client is used to compress text files." << std::endl;
}