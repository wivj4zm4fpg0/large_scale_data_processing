#include <fstream>
#include "../include/make_directory.h"

int main(int argc, char* argv[])
{
    fs::path pwd = string(getenv("PWD"));
    fs::path input_path = pwd / fs::path(argv[1]);
    fs::path output_path = pwd / fs::path(argv[2]);
    fs::path log_path = fs::path(argv[3]);

    string image_path_string, output_path_full_string;
    fs::path output_path_full;

    string command = "convert ", option = " -quality 50 ";
    ifstream exist_file;
    ofstream log_file(log_path.string(), ios::app);
    int count = 0;

    make_directory(input_path, output_path);

    log_file.is_open();
    for (auto & class_dir : fs::directory_iterator(input_path)) {
        for (auto & images_dir : fs::directory_iterator(class_dir)) {
            for (auto & image_path : fs::directory_iterator(images_dir)) {

                image_path_string = fs::path(image_path).string();
                if (image_path_string.find(".jpg") != string::npos) {

                    output_path_full = output_path / image_path_string.substr(string(input_path).length());
                    output_path_full_string = output_path_full.string();

                    exist_file = ifstream(output_path_full_string);
                    if (exist_file) {
                        continue;
                    } else {
                        system((command + image_path_string + option + output_path_full_string).c_str());
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
