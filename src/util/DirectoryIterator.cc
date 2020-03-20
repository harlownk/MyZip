// Copyright Nicholas Harlow

#include <string>
#include <sys/types.h>
#include <dirent.h>

#include "DirectoryIterator.h"

namespace util {

DirectoryIterator::DirectoryIterator(std::string dirName) : next_(nullptr) {
  dir_ = opendir(dirName.c_str());
}

DirectoryIterator::~DirectoryIterator() {
  closedir(dir_);
}

bool DirectoryIterator::HasNext() {
  if (dir_!= nullptr) {
    if (next_ == NULL) {
      next_ = readdir(dir_);
      return next_ != nullptr;
    } else {
      return true;
    }
  }
  return false;
}

SystemFile DirectoryIterator::GetNext() {
  if (next_ == nullptr) {
    next_ = readdir(dir_);
    if (next_ == nullptr) {
      return NULL;
    }
    return SystemFile(next_);
  } else {
    SystemFile result(next_);
    next_ = nullptr;
    return result;
  }
}

}