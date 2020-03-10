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
  

}