// Copyright Nicholas Harlow

#include <string>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>

#include "SystemFile.h"

namespace util {

SystemFile::SystemFile(std::string filePath) {
  if (!filePath.substr(filePath.size() - 1).compare("/")) {
    filePath_ = filePath.substr(0, filePath.size() - 1);
  } else {
    filePath_ = filePath;
  }
}

SystemFile::~SystemFile() {}

bool SystemFile::IsDirectory() {
  std::string filename = GetFilePath();
  struct stat statInfo;
  if (stat(filename.c_str(), &statInfo)) {
    // Error happened here somewhere
    return false;
  }
  return S_ISDIR(statInfo.st_mode);
}

bool SystemFile::IsFile() {
  std::string filename = GetFilePath();
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
  std::string filename = GetFilePath();
  if (!filename.substr(filename.size() - 3).compare("/..") || 
      !filename.substr(filename.size() - 2).compare("/.")) {
    return true;
  } else {
    return false;
  }
  
}

std::string SystemFile::GetFilePath() {
  return filePath_;
}


std::string SystemFile::GetFileName() {
  return filePath_.substr(filePath_.find_last_of('/'));
}

}  // namespace util