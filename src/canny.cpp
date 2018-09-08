#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    Mat image = imread(argv[1]);
    if (image.empty())
    {
        cout << "Image loading failed." << endl;
        return -1;
    }
    cvtColor(image, image, CV_BGR2GRAY);
    blur(image, image, Size(3, 3));
    Canny(image, image, 50, 100, 3);
    imshow("image", image);
    waitKey(0);
    return 0;
}
