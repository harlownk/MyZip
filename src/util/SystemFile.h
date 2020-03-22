// Copyright Nicholas Harlow

#ifndef SRC_UTIL_SYSTEMFILE_H_
#define SRC_UTIL_SYSTEMFILE_H_

#include <dirent.h>
#include <string>

namespace util {
  
class SystemFile {
 public:
  SystemFile(std::string filePath);
  ~SystemFile();
  bool IsDirectory();
  bool IsFile();
  bool IsRelativeDir();
  std::string GetFileName();
 private:
  std::string filePath_;
  // struct dirent *fileEntry_;
};

}  // namespace util

#endif  // SRC_SYSTEMFILE_H_