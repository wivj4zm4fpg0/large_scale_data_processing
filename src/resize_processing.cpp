#include "../include/base.hpp"

class Resize : public Base {
public:
  void processing(string &input_path, string &output_path) override {
    system(("convert " + input_path + " -quality 50 " + output_path).c_str());
  }

  Resize(char** argv) : Base(argv) {

  }
};

int main(int argc, char** argv) {
  Resize *resize = new Resize(argv);
  resize->large_scale_data_processing();
  return 0;
}
