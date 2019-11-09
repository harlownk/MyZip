// Copyright Nicholas Harlow

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <string>
#include <unordered_map>

static void PrintCommandHelp();
static void ZipFile(std::string file_name);
static int WriteZipFile(std::string file_name, 
                        std::unordered_map<int, std::string> *encodingMap);
static void UnzipFile(std::string file_name);

#endif  // SRC_CLIENT_H_