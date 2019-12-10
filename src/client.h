// Copyright Nicholas Harlow

#ifndef SRC_CLIENT_H_
#define SRC_CLIENT_H_

#include <string>
#include <unordered_map>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define ZIP_HEADER_LENGTH 32

static void PrintCommandHelp();
static void PrintUsage();
static void ZipFile(std::string file_name);
static int WriteZipFile(std::string orig_file_name, 
                        std::unordered_map<int, std::string> *encodingMap);
static void UnzipFile(std::string file_name);

// Converts the bitstring to the corresponding bitstream that is then written
// to the ofstream.  Will only write bitstrings that are of length % 8 == 0.  
// Any bitstring provided that is not of that length, will have 0s padded to the
// end to be the proper length to write to a file.
// 
// Returns false if there is any error writing to the file, otherwise returns
// true.
static bool WriteBitStringToFile(std::string bitString, std::ofstream &outfile);


#endif  // SRC_CLIENT_H_