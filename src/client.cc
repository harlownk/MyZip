// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <sstream>
#include <climits>
#include <fstream>

#include "client.h"
#include "huffmanzipper/HuffmanZipper.h"
#include "util/DirectoryIterator.h"

using std::string;
using huffmanzipper::HuffmanZipper;
using util::DirectoryIterator;
using util::SystemFile;

int main(int argc, char** argv) {
  // Do Preliminary checks.
  if (argc == 1) {
    // Print client help/usage
    PrintCommandHelp();
  } else if (argc != 3) {
    PrintUsage();
  }


  if (string(argv[1]).compare("f") == 0) {
    std::string fileName = string(argv[2]);
    TraverseFileSystem(fileName, "");  
    return EXIT_SUCCESS;
  }

  // TODO Add directory support.
  // Check if file given is directory or reg file
  // If dir: Recursively zip each directory by zipping files recursively.
  // If file: zip given file.

  // Execute the commands.
  string file_name(argv[2]);
  // SystemFile inputFile(file_name);
  // if (inputFile.IsFile()) {

  // } else if (inputFile.IsDirectory()) {

  // }

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
    std::cout << "Unzipping " << file_name << std::endl;
    if (zipper.UnzipFile(file_name)) {
      std::cout << "Unzip Successful." << std::endl;
    } else {
      std::cout << "Unzip Unsuccessful." << std::endl;
      exit(EXIT_FAILURE);
    }
  } else {
    std::cerr << "mode " << argv[1] << " not recognized." << std::endl;
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

static void TraverseFileSystem(std::string currDirPath, std::string zipDirPath) {
  HuffmanZipper zipper;
  DirectoryIterator dirIter(currDirPath);
  while (dirIter.HasNext()) {
    util::SystemFile nextFile = dirIter.GetNext();
    if (nextFile.IsDirectory() && !nextFile.IsRelativeDir()) {
      // Get path of zipp directory,
      // zip directory by placing all files into this directory.
      std::cout << nextFile.GetFilePath() << "/" << std::endl;
      std::string newZipPathDir = zipDirPath + nextFile.GetFileName() + ".mzip";
      std::cout << newZipPathDir << "/" << std::endl;
      TraverseFileSystem(nextFile.GetFilePath(), newZipPathDir);
    } else if (nextFile.IsFile()) {
      // Zip it
      std::string currFileName = nextFile.GetFilePath();
      // zipper.ZipFile(currFileName);
      // Make sure the zipped file is now in the zipped directory.
      std::cout << zipDirPath << nextFile.GetFileName() << std::endl;
    }
  }
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
