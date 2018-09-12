#include <opencv2/opencv.hpp>
#include "../include/base.hpp"
using namespace::cv;

class Canny_processing : public Base {
private:
  Mat image;
public:
  void processing(string &input_path, string &output_path) override {
    this->image = imread(input_path);
    if (image.empty()) {
      cout << "Image loading failed :" << input_path << endl;
      exit(1);
    }
    cvtColor(this->image, this->image, CV_BGR2GRAY);
    blur(this->image, this->image, Size(3, 3));
    Canny(this->image, this->image, 50, 100, 3);
    imwrite(output_path, this->image);
  }

  Canny_processing(char** argv) : Base(argv) {
    
  }
};

int main(int argc, char** argv) {
  Canny_processing* canny = new Canny_processing(argv);
  canny->large_scale_data_processing();
  return 0;
}
