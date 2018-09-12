#include <opencv2/opencv.hpp>
#include "../include/base.hpp"
using namespace::cv;

class Gause : public Base {
private:
  Mat image;
  float m;
  float sigma;
  Mat noise;
public:
  void processing(string &input_path, string &output_path) override {
    this->image = imread(input_path);
    if (image.empty()) {
      cout << "Image loading failed :" << input_path << endl;
      exit(1);
    }

	this->noise = Mat(this->image.size(), this->image.type());
	randn(this->noise, this->m, this->sigma); //mean and variance
	this->image += this->noise;
    imwrite(output_path, this->image);
  }

  Gause(char** argv) : Base(argv) {
    this->m = (10, 12, 34);
    this->sigma = (1, 5, 50);
  }
};

int main(int argc, char** argv) {
  Gause* gause = new Gause(argv);
  gause->large_scale_data_processing();
  return 0;
}
