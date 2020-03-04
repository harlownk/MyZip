// Copyright Nicholas Harlow

#ifndef SRC_UTIL_FILESYSTEMITERATOR_H_
#define SRC_UTIL_FILESYSTEMITERATOR_H_

#include <string>

namespace util {

class FileSystemIterator {
 public:
  FileSystemIterator(std::string dirName);
  ~FileSystemIterator();
  boolean HasNextFile();
  boolean HasNextDir();
  SystemFile GetNextFile();
  SystemFile GetNextDir();
 private:
  DIR *dir_;
  SystemFile nextFile_;
  SystemFile nextDir_;
};  // class FileSystemIterator

}  // namespace util 

#endif  // SRC_FILESYSTEMITERATOR_H_