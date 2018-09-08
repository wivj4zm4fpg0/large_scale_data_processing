#ifndef _INCLUDE_MAKE_DIRECTORY_
#define _INCLUDE_MAKE_DIRECTORY_

#include <string>
#include <iostream>
#include <experimental/filesystem>
using namespace::std;
namespace fs = std::experimental::filesystem;
extern void make_directory(fs::path &input_path, fs::path &output_path);

#endif
