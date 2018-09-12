#include <opencv2/opencv.hpp>
#include "../include/base.hpp"
using namespace::cv;

const double AMOUNT = 0.05;

class Salt_pepper : public Base {
private:
  Mat image;
  int width;
  int height;
  int y;
  int x;
public:
  void processing(string &input_path, string &output_path) override {
    this->image = imread(input_path);
    if (image.empty()) {
      cout << "Image loading failed :" << input_path << endl;
      exit(1);
    }

    this->width = this->image.size().width;
    this->height = this->image.size().height;
	for (this->y = 0; this->y < this->height; this->y++) {
      cv::Vec3b *srcp = this->image.ptr<cv::Vec3b>(this->y);
      for (this->x = 0; this->x < this->width; this->x++) {
        if ((double)rand() / RAND_MAX <= AMOUNT) {
          srcp[this->x][0] = 255;
          srcp[this->x][1] = 255;
          srcp[this->x][2] = 255;
        }
        if ((double)rand() / RAND_MAX <= AMOUNT) {
          srcp[this->x][0] = 0;
          srcp[this->x][1] = 0;
          srcp[this->x][2] = 0;
        }
      }
	}
    imwrite(output_path, this->image);
  }

  Salt_pepper(char** argv) : Base(argv) {
    
  }
};

int main(int argc, char** argv) {
  Salt_pepper* salt_pepper = new Salt_pepper(argv);
  salt_pepper->large_scale_data_processing();
  return 0;
}
