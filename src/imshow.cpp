#include <iostream>
#include <opencv2/opencv.hpp>
using namespace::cv;
using namespace::std;

int main(int argc, char** argv)
{
    Mat image = imread(argv[1]);
    imshow("image", image);
    waitKey(0);
    return(0);
}
