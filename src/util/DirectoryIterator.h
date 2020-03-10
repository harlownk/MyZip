// Copyright Nicholas Harlow

#ifndef SRC_UTIL_DIRECTORYITERATOR_H_
#define SRC_UTIL_DIRECTORYITERATOR_H_

#include <string>
#include <sys/types.h>
#include <dirent.h>

#include "SystemFile.h"

namespace util {

class DirectoryIterator {
 public:
  DirectoryIterator(std::string dirName);
  ~DirectoryIterator();
  bool HasNext();
  SystemFile GetNext();
 private:
  DIR *dir_;
  SystemFile *next_;
};  // class DirectoryIterator

}  // namespace util 

#endif  // SRC_UTIL_DIRECTORYITERATOR_H_