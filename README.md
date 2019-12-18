# Simple Zip and Unzip

## Basic Usage
- ./client &lt;mode&gt; &lt;filename&gt;
- mode is either 'z' to zip, or 'u' to unzip

## Building
Now creates a bin folder for the executable, and a build folder for build files.

## Installation?
Requires boost libraries. 
Mine installed via <code>$ sudo apt-get install libboost-all-dev</code>

## Project Todos:
 - [ ] Transition to Cmake for the build system. (Ideally done myself, maybe find a Cmake to use)
 - [ ] Once the base project is made, and switched to Cmake, add unit tests using [GoogleTest](https://github.com/google/googletest)