#include <opencv2/opencv.hpp>
#include "../include/make_directory.h"
using namespace::cv;

Mat image;

void canny(string &input_path, string &output_path)
{
    image = imread(input_path);
    if (image.empty()) {
        cout << "Image loading failed :" << input_path << endl;
        exit(1);
    }
    cvtColor(image, image, CV_BGR2GRAY);
    blur(image, image, Size(3, 3));
    Canny(image, image, 50, 100, 3);
    imwrite(output_path, image);
}

int main(int argc, char* argv[])
{
    fs::path pwd = string(getenv("PWD"));
    fs::path input_path = pwd / fs::path(argv[1]);
    fs::path output_path = pwd / fs::path(argv[2]);
    fs::path log_path = fs::path(argv[3]);

    string image_path_string, output_path_full_string;
    fs::path output_path_full;

    ifstream exist_file;
    ofstream log_file(log_path.string(), ios::app);
    int count = 0;

    make_directory(input_path, output_path);

    log_file.is_open();
    for (auto & class_dir : fs::directory_iterator(input_path)) {
        for (auto & images_dir : fs::directory_iterator(class_dir)) {
            for (auto & image_path : fs::directory_iterator(images_dir)) {

                image_path_string = fs::path(image_path).string();
                if (image_path_string.find(".jpg") != string::npos) { // do image_path_string contains jpg image ?

                    output_path_full = output_path / image_path_string.substr(string(input_path).length()); // add class_dir/images_dir/image_path to output_path
                    output_path_full_string = output_path_full.string();

                    exist_file = ifstream(output_path_full_string);
                    if (exist_file) {
                        continue;
                    } else {
                        canny(image_path_string, output_path_full_string);
                        log_file << output_path_full_string << endl;
                    }
                }
            }
            cout << ++count << " " << images_dir << endl;
        }
    }
    log_file.close();

    return 0;
}
