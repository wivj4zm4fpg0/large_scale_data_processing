#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cudafilters.hpp>

#include <iostream>

using namespace std;
using namespace cv;

void canny(Mat &image)
{
    cuda::GpuMat gpu_image(image);
    cuda::cvtColor(gpu_image, gpu_image, COLOR_BGR2GRAY);
    Ptr<cuda::Filter> blur = cuda::createBoxFilter(gpu_image.type(), gpu_image.type(), Size(3, 3));
    blur->apply(gpu_image, gpu_image);
    Ptr<cuda::CannyEdgeDetector> canny = cuda::createCannyEdgeDetector(50.0, 100.0, 3, false);
    canny->detect(gpu_image, gpu_image);
    gpu_image.download(image);
}

int main(int argc, char* argv[])
{
    Mat image = imread("lena.png");
    if (image.empty())
    {
        return -1;
    }
    canny(image);
    imshow("image", image);
    waitKey(0);

    return 0;
}

