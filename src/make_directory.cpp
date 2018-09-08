#include <string>
#include <iostream>
#include <experimental/filesystem>
using namespace::std;
namespace fs = std::experimental::filesystem;

void make_directory(fs::path &input_file, fs::path &output_file)
{
    fs::path output_images_dir;
    string images_dir_string;

    for (auto & class_dir : fs::directory_iterator(input_file)) {
        for (auto & images_dir : fs::directory_iterator(class_dir)) {
            images_dir_string = fs::path(images_dir).string();
            output_images_dir = output_file / fs::path(images_dir_string.substr(input_file.string().length()));
            fs::create_directories(output_images_dir);
            cout << "create "  << output_images_dir << endl;
        }
    }
}
