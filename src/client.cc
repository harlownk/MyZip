// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>

#include "client.h"

int main(int argc, char** argv) {
  if (argc == 1) {
    // Print client help 
    PrintCommandHelp();
    exit(EXIT_SUCCESS);
  } else if (argc != 2) {
    // Make sure to update when dev continues.
    std::cerr << "Usage: ./client <filename>" << std::endl;
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

void PrintCommandHelp() {
    std::cout << "./client is used to compress text files." << std::endl;
}