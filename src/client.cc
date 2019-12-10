// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <sstream>
#include <climits>
#include <fstream>

#include "client.h"
#include "HuffmanZipper.h"
#include "ByteInventory.h"
#include "HuffmanTree.h"

using std::string;

int main(int argc, char** argv) {
  // Do Preliminary checks.
  if (argc == 1) {
    // Print client help/usage
    PrintCommandHelp();
  } else if (argc != 3) {
    PrintUsage();
  }

  // Execute the commands.
  string file_name(argv[2]);
  HuffmanZipper zipper;
  if (string(argv[1]).compare("z") == 0) {  // Zip mode
    std::cout << "Zipping " << file_name << "..." << std::endl;
    if (zipper.ZipFile(file_name)) {
      std::cout << "Zip Successful." << std::endl;
    } else {
      std::cout << "Zip Unsuccessful." << std::endl;
      exit(EXIT_FAILURE);
    }
  } else if (string(argv[1]).compare("u") == 0) {  // Unzip mode
    zipper.UnzipFile(file_name);
  } else {
    std::cerr << "mode " << argv[1] << " not recognized." << std::endl;
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);

}

static void PrintUsage() {
  // Make sure to update when dev continues.
  std::cerr << "Usage: ./client <mode> <filename>" << std::endl;
  exit(EXIT_FAILURE);
}

static void PrintCommandHelp() {
  std::cout << "./client is used to compress text files." << std::endl;
  exit(EXIT_SUCCESS);
}
