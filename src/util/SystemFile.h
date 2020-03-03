// Copyright Nicholas Harlow

#ifndef SRC_UTIL_SYSTEMFILE_H_
#define SRC_UTIL_SYSTEMFILE_H_

#include <dirent.h>
#include <string>

namespace util {
  
class SystemFile {
 public:
  SystemFile(struct dirent *fileEntry);
  ~SystemFile();
  bool IsDirectory();
  bool IsFile();
  std::string GetFileName();
 private:
  struct dirent *fileEntry_;
};

}  // namespace util

#endif  // SRC_SYSTEMFILE_H_