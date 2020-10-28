# Simple Zip and Unzip

## Project Reflection
### Things I learned
- Accessing the power of the boost libraries.
- Details on reading and writing bindary files using cpp
- How to access and iterate through the filesystem.
- Practiced designing and using a defined file structure that would fit my needs.

### Difficulties Encountered
- Getting used to semantics around cpp streams for file access.
- Learning the best way to handle dependencies and libraries in cpp.

### Things I would do differently
- Definitely wouldn't use bitstrings for handling bits/bytes.
  - Make a BitStream utility that can handle that work for me at a low level both for speed and for easier use than handling bitstring everywhere.
- Maybe create my own Makefile, or use some other build system for cpp so I can learn more about the building/linking process.

### Next Steps
- Add concurrent/parallel processing of directories.  Each directory is handled by a thread.
  - Will be a good opportunity to learn how to implement a thread pool with pthreads or cpp threads in cpp11
- Create a bitstream utility to handle bit level operations.

## Basic Usage
- ./client &lt;mode&gt; &lt;filename&gt;
- mode is either 'z' to zip, or 'u' to unzip

## Installation?
Requires boost libraries. 
Mine installed via <code>$ sudo apt-get install libboost-all-dev</code>
