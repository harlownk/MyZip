// Copyright Nicholas Harlow

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <string>
#include <unordered_map>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024

static void PrintCommandHelp();
static void ZipFile(std::string file_name);
static int WriteZipFile(std::string orig_file_name, 
                        std::unordered_map<int, std::string> *encodingMap);
static void UnzipFile(std::string file_name);
static void WriteBitStringToFile(std::string bitString, FILE *file);


#endif  // SRC_CLIENT_H_