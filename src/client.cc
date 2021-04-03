// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <sstream>
#include <climits>
#include <fstream>
#include <thread>
#include <sys/stat.h>
#include <sys/types.h>

#include "client.h"
#include "huffmanzipper/HuffmanZipper.h"
#include "util/DirectoryIterator.h"
#include "util/ThreadPool.h"

using std::string;
using huffmanzipper::HuffmanZipper;
using util::DirectoryIterator;
using util::SystemFile;

  // TODO Error detection still needs done.
  // TODO Make sure that how we exit is consistant through the project (EXIT_SUCCESS) etc.

static const string ZIP_ENDING = ".mzip";

void hello() {
  std::cout << "Hello" << std::endl;
}

class ZipDirThread {
 public:
  ZipDirThread(std::string old, std::string newFile) {
    this->oldFile = old;
    this->newFile = newFile;
  }

  void operator() () const {
    ZipDirectory(this->oldFile, this->newFile);
  }
  std::string oldFile;
  std::string newFile;
};

int main(int argc, char** argv) {
  // Do Preliminary checks.
  if (argc == 1) {
    // Print client help/usage
    PrintCommandHelp();
  } else if (argc != 3) {
    PrintUsage();
  }

  // Create a thread pool.
  // std::thread helloThread(hello);
  // Execute the commands.
  string givenFileName = string(argv[2]);
  SystemFile inputFile(givenFileName);
  string fileName = inputFile.GetFilePath();
  if (string(argv[1]).compare("z") == 0) {  // Zip mode
    // If FILE:
    bool success;
    if (inputFile.IsFile()) {
      success = ZipFile(fileName, fileName + ZIP_ENDING);
    } else if (inputFile.IsDirectory() && !inputFile.IsRelativeDir()) {
      mkdir((fileName + ZIP_ENDING).c_str(), 00777);
      
      // util::ThreadPool<ZipDirThread, void(), void> pool(4);
      
      success = ZipDirectory(fileName, fileName + ZIP_ENDING);
    } else {
      // Isn't zipable
      success = false;
    }
    if (success) {
      return EXIT_SUCCESS;   
    } else {
      return EXIT_FAILURE;
    }
  } else if (string(argv[1]).compare("u") == 0) {  // Unzip mode
    // If File:
    bool success;
    if (inputFile.IsFile()) {
      success = UnzipFile(fileName, fileName.substr(0, fileName.size() - ZIP_ENDING.size()));
    } else if (inputFile.IsDirectory() && !inputFile.IsRelativeDir()) {
      std::string fileName = string(argv[2]);
      std::string destPath = fileName.substr(0, fileName.size() - ZIP_ENDING.size());
      mkdir((destPath).c_str(), 00777);
      success = UnzipDirectory(fileName, destPath);
    } else {
      // Isn't unzipable
      success = false;
    }
    if (success) {
      return EXIT_SUCCESS;   
    } else {
      return EXIT_FAILURE;
    }
  } else {
    std::cerr << "mode " << argv[1] << " not recognized." << std::endl;
    return EXIT_FAILURE;
  }
}

static bool ZipFile(std::string fileLocation, std::string zipDestination) {
  HuffmanZipper zipper;
  std::cout << "Zipping " << fileLocation << "..." << std::endl;
  if (zipper.ZipFile(fileLocation, zipDestination)) {
    std::cout << "Zip Successful." << std::endl;
  } else {
    std::cout << "Zip Unsuccessful." << std::endl;
    return false;
  }
  return true;
}

static bool UnzipFile(std::string fileLocation, std::string zipDestination) {
  HuffmanZipper zipper;
  std::cout << "Unzipping " << fileLocation << std::endl;
  if (zipper.UnzipFile(fileLocation, zipDestination)) {
    std::cout << "Unzip Successful." << std::endl;
  } else {
    std::cout << "Unzip Unsuccessful." << std::endl;
    return false;
  }
  return true;
}

static bool ZipDirectory(std::string currDirPath, std::string zipDirPath) {
  HuffmanZipper zipper;
  DirectoryIterator dirIter(currDirPath);
  bool currentZipSuccessful = true;
  while (dirIter.HasNext() && currentZipSuccessful) {
    util::SystemFile nextFile = dirIter.GetNext();
    if (nextFile.IsDirectory() && !nextFile.IsRelativeDir()) {
      // Get path of zipp directory,
      // zip directory by placing all files into this directory.
      std::string newZipPathDir = zipDirPath + nextFile.GetFileName() + ZIP_ENDING;
      mkdir(newZipPathDir.c_str(), 00777);
      currentZipSuccessful = ZipDirectory(nextFile.GetFilePath(), newZipPathDir);
    } else if (nextFile.IsFile()) {
      // Zip it
      std::string currFileName = nextFile.GetFilePath();
      std::string zipFileName = zipDirPath + "/" + nextFile.GetFileName() + ZIP_ENDING;
      currentZipSuccessful = zipper.ZipFile(currFileName, zipFileName);
      // Make sure the zipped file is now in the zipped directory.
    }
  }
  return currentZipSuccessful;
}

static bool UnzipDirectory(std::string currDirPath, std::string zipDirPath) {
  // TODO This is 'hard coded' such that the file MUST have the proper zip ending
  //   IF it doesn't then it won't construct the paths properly.
  HuffmanZipper zipper;
  DirectoryIterator dirIter(currDirPath);
  bool currentUnzipSuccessful = true;
  while (dirIter.HasNext() && currentUnzipSuccessful) {
    util::SystemFile nextFile = dirIter.GetNext();
    if (nextFile.IsDirectory() && !nextFile.IsRelativeDir()) {
      std::string currFileName = nextFile.GetFileName();
      std::string newZipPathDir = zipDirPath + "/" + (currFileName.substr(0, currFileName.size() - ZIP_ENDING.size()));
      mkdir(newZipPathDir.c_str(), 00777);
      currentUnzipSuccessful = UnzipDirectory(nextFile.GetFilePath(), newZipPathDir);
    } else if (nextFile.IsFile()) {
      // Unzip it
      std::string currFilePath = nextFile.GetFilePath();
      std::string currFileName = nextFile.GetFileName();
      std::string zipFileName = zipDirPath + (currFileName.substr(0, currFileName.size() - ZIP_ENDING.size()));
      currentUnzipSuccessful = zipper.UnzipFile(currFilePath, zipFileName);
    }
  }
  return currentUnzipSuccessful;
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
