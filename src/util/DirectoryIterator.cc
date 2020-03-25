// Copyright Nicholas Harlow

#include <string>
#include <sys/types.h>
#include <dirent.h>

#include "DirectoryIterator.h"

namespace util {

DirectoryIterator::DirectoryIterator(std::string dirName) : next_(nullptr) {
  dirName_ = dirName;
  if (dirName_.back() == '/') {
    dirName_ = dirName_.substr(0, dirName_.size() - 1);
  }
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
      return SystemFile("");
    }
    std::string filename(next_->d_name);
    return SystemFile(dirName_ + "/" + filename);
  } else {
    std::string filename(next_->d_name);
    SystemFile result(dirName_ + "/" + filename);
    next_ = nullptr;
    return result;
  }
}

}