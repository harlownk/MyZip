// Copyright Nicholas Harlow

#include <string>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>

#include "SystemFile.h"

namespace util {

SystemFile::SystemFile(struct dirent *fileEntry) {
  fileEntry_ = fileEntry;
}

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
  // TODO ENOENT error is happening here on occasion. Happens
  // when I give a directory that is deeper than where client is instantiated.
  // I think the filename isn't 'absolute enough' for stat to work. Wont even 
  // work on directories in directories that are that deep.
  if (stat(filename.c_str(), &statInfo)) {
    // Error happened here somewhere
    return false;
  }
  return S_ISREG(statInfo.st_mode);
}



std::string SystemFile::GetFileName() {
  std::string result(fileEntry_->d_name);
  return result;
}

}  // namespace util