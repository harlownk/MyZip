// Copyright Nicholas Harlow

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <sstream>
#include <climits>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

#include "client.h"
#include "huffmanzipper/HuffmanZipper.h"
#include "util/DirectoryIterator.h"

using std::string;
using huffmanzipper::HuffmanZipper;
using util::DirectoryIterator;
using util::SystemFile;

static const string ZIP_ENDING = ".mzip";

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
    mkdir((fileName + ZIP_ENDING).c_str(), 00777);
    ZipDirectory(fileName, fileName + ZIP_ENDING);  
    return EXIT_SUCCESS;
  }
  if (string(argv[1]).compare("t") == 0) {
    std::string fileName = string(argv[2]);
    std::string destPath = fileName.substr(0, fileName.size() - ZIP_ENDING.size());
    mkdir((destPath).c_str(), 00777);
    UnzipDirectory(fileName, destPath);  
    return EXIT_SUCCESS;
  }

  // TODO Add directory support.
  // Check if file given is directory or reg file
  // If dir: Recursively zip each directory by zipping files recursively.
  // If file: zip given file.
  // TODO Error detection still needs done.

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

static bool ZipFile(std::string fileLocation, std::string zipDestination) {
  return true;
}
static bool UnzipFile(std::string fileLocation, std::string zipDestination) {
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
