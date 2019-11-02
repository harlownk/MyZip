// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>

#include "client.h"

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
    // Make a byte inventory of the file. (Include EOF, Include zip header seperator)
    // Make an encoding tree
    // Make translation lookup-table from tree
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

void PrintCommandHelp() {
    std::cout << "./client is used to compress text files." << std::endl;
}