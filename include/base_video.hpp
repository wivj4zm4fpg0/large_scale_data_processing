#ifndef _INCLUDE_BASE_
#define _INCLUDE_BASE_

#include "make_directory.hpp"

class Base_Video {
private:
  char** argv;
public:
  virtual void processing(string &input_path, string &output_path) = 0;
  void large_scale_data_processing();

  Base_Video(char** argv);
};

#endif
