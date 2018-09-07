#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cudafilters.hpp>

#include <iostream>
#include <filesystem>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;

void canny_gpu(Mat &image)
{
    cuda::GpuMat gpu_image(image);
    Ptr<cuda::Filter> blur = cuda::createBoxFilter(gpu_image.type(), gpu_image.type(), Size(3, 3));
    Ptr<cuda::CannyEdgeDetector> canny = cuda::createCannyEdgeDetector(50.0, 100.0, 3, false);

    cuda::cvtColor(gpu_image, gpu_image, COLOR_BGR2GRAY);
    blur->apply(gpu_image, gpu_image);
    canny->detect(gpu_image, gpu_image);
    gpu_image.download(image);
}

void blur_time_comparison(Mat &image, int n_count)
{
    cvtColor(image, image, COLOR_BGR2GRAY);

    int64 tickCount = 0;
    cuda::GpuMat gpu_image(image);
    cuda::GpuMat out_gpu(gpu_image.size(), gpu_image.type());
    Ptr<cuda::Filter> filter = cuda::createBoxFilter(gpu_image.type(), gpu_image.type(), Size(3, 3));
    Mat out_cpu(image.size(), image.type());

    for (int i = 0; i < n_count; i++)
    {
        tickCount = getTickCount();
        filter->apply(gpu_image, out_gpu);
        cout << "GPU blur time = " << (getTickCount() - tickCount) / getTickFrequency() << endl;
    }

    puts("");

    for (int i = 0; i < n_count; i++)
    {
        tickCount = getTickCount();
        blur(image, out_cpu, Size(3, 3));
        cout << "CPU blur time = " << (getTickCount() - tickCount) / getTickFrequency() << endl;
    }
}

void canny_time_comparison(Mat &image, int n_count)
{
    cvtColor(image, image, COLOR_BGR2GRAY);
    blur(image, image, Size(3, 3));

    int64 tickCount = 0;
    cuda::GpuMat gpu_image(image);
    cuda::GpuMat out_gpu(gpu_image.size(), gpu_image.type());
    Ptr<cuda::CannyEdgeDetector> filter = cuda::createCannyEdgeDetector(50, 100, 3, false);
    Mat out_cpu(image.size(), image.type());

    for (int i = 0; i < n_count; i++)
    {
        tickCount = getTickCount();
        filter->detect(gpu_image, out_gpu);
        cout << "GPU canny time = " << (getTickCount() - tickCount) / getTickFrequency() << endl;
    }

    puts("");

    for (int i = 0; i < n_count; i++)
    {
        tickCount = getTickCount();
        Canny(image, out_cpu, 50, 100, 3, false);
        cout << "CPU canny time = " << (getTickCount() - tickCount) / getTickFrequency() << endl;
    }
}

void canny_blur_time_comparison(Mat &image, int n_count)
{
    cvtColor(image, image, COLOR_BGR2GRAY);

    int64 tickCount = 0;
    cuda::GpuMat gpu_image(image);
    cuda::GpuMat out_gpu(gpu_image.size(), gpu_image.type());
    Ptr<cuda::Filter> blur_filter = cuda::createBoxFilter(gpu_image.type(), gpu_image.type(), Size(3, 3));
    Ptr<cuda::CannyEdgeDetector> canny_filter = cuda::createCannyEdgeDetector(50, 100, 3, false);
    Mat out_cpu(image.size(), image.type());

    // GPU only
    for (int i = 0; i < n_count; i++)
    {
        tickCount = getTickCount();
        blur_filter->apply(gpu_image, out_gpu);
        canny_filter->detect(out_gpu, out_gpu);
        cout << "GPU canny time = " << (getTickCount() - tickCount) / getTickFrequency() << endl;
    }

    puts("");

    // CPU only
    for (int i = 0; i < n_count; i++)
    {
        tickCount = getTickCount();
        blur(image, out_cpu, Size(3, 3));
        Canny(out_cpu, out_cpu, 50, 100, 3, false);
        cout << "CPU canny time = " << (getTickCount() - tickCount) / getTickFrequency() << endl;
    }

    puts("");

    // CPU and GPU
    for (int i = 0; i < n_count; i++)
    {
        tickCount = getTickCount();
        blur_filter->apply(gpu_image, out_gpu);
        out_gpu.download(out_cpu);
        Canny(out_cpu, out_cpu, 50, 100, 3, false);
        cout << "Hybrid canny time = " << (getTickCount() - tickCount) / getTickFrequency() << endl;
    }
}

int main(int argc, char* argv[])
{
    Mat image = imread("lena.png");
    int n_count = 30;

    if (image.empty())
    {
        return -1;
    }
    canny_blur_time_comparison(image, n_count);

    return 0;
}

