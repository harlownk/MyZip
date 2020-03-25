// Copyright Nicholas Harlow

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <string>
#include <unordered_map>

static bool ZipFile(std::string fileLocation, std::string zipDestination);
static bool UnzipFile(std::string fileLocation, std::string zipDestination);
static bool ZipDirectory(std::string currDirPath, std::string zipDirPath);
static bool UnzipDirectory(std::string currDirPath, std::string zipDirPath);
static void PrintCommandHelp();
static void PrintUsage();


#endif  // SRC_CLIENT_H_