// Copyright Nicholas Harlow

#include <string>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>

#include "SystemFile.h"

namespace util {

SystemFile::SystemFile(std::string filePath) : filePath_(filePath) {}

SystemFile::~SystemFile() {}

bool SystemFile::IsDirectory() {
  std::string filename = GetFileName();
  struct stat statInfo;
  if (stat(filename.c_str(), &statInfo)) {
    // Error happened here somewhere
    return false;
  }
  return S_ISDIR(statInfo.st_mode);
}

bool SystemFile::IsFile() {
  std::string filename = GetFileName();
  struct stat statInfo;
  if (stat(filename.c_str(), &statInfo)) {
    // Error happened here somewhere
    return false;
  }
  return S_ISREG(statInfo.st_mode);
}

bool SystemFile::IsRelativeDir() {
  if (!IsDirectory()) {
    return false;
  }
  std::string filename = GetFileName();
  if (!filename.substr(filename.size() - 3).compare("/..") || 
      !filename.substr(filename.size() - 2).compare("/.")) {
    return true;
  } else {
    return false;
  }
  
}



std::string SystemFile::GetFileName() {
  return filePath_;
}

}  // namespace util