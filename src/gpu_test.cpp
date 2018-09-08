#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    // Mat src = imread("lena.png", IMREAD_UNCHANGED), dst;
    Mat src = imread("lena.png"), dst;
    if (src.empty())
    {
        return -1;
    }

    cuda::GpuMat d_src(src), d_dst;
    cuda::cvtColor(d_src, d_dst, COLOR_BGR2GRAY);

    // highgui(normal)を使った表示
    d_dst.download(dst); // ホストメモリに転送する
    namedWindow("normal", WINDOW_AUTOSIZE);
    imshow("normal", dst);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
