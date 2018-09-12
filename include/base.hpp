#ifndef _INCLUDE_BASE_
#define _INCLUDE_BASE_

// include "make_directory.hpp"
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
using namespace::std;
namespace fs = std::experimental::filesystem;

class Base {
private:
  char** argv;
public:
  void make_directory(fs::path &input_path, fs::path &output_path);
  virtual void processing(string &input_path, string &output_path) = 0;
  void large_scale_data_processing();

  Base(char** argv);
};

#endif
