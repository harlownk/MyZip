// Copyright Nicholas Harlow

#include <string>
#include <dirent.h>

#include "SystemFile.h"

namespace util {

SystemFile::SystemFile(struct dirent *fileEntry) {
  fileEntry_ = fileEntry;
}

SystemFile::~SystemFile() {}

bool SystemFile::IsDirectory() {
  
}

bool SystemFile::IsFile() {

}

std::string SystemFile::GetFileName() {
  std::string result(fileEntry_->d_name);
  return result;
}

}  // namespace util