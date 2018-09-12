#include "../include/base.hpp"

void Base::make_directory(fs::path &input_path, fs::path &output_path) {
  fs::path output_images_dir;
  string images_dir_string;

  for (auto & class_dir : fs::directory_iterator(input_path)) {
    for (auto & images_dir : fs::directory_iterator(class_dir)) {
      images_dir_string = fs::path(images_dir).string();
      output_images_dir = output_path / fs::path(images_dir_string.substr(input_path.string().length()));
      fs::create_directories(output_images_dir);
      cout << "create " << output_images_dir << endl;
    }
  }
}

void Base::large_scale_data_processing() {
  fs::path pwd = string(getenv("PWD"));
  fs::path input_path = pwd / fs::path(this->argv[1]);
  fs::path output_path = pwd / fs::path(this->argv[2]);
  fs::path log_path = fs::path(this->argv[3]);

  string image_path_string, output_path_full_string;
  fs::path output_path_full;

  ifstream exist_file;
  ofstream log_file(log_path.string(), ios::app);
  int count = 0;

  this->make_directory(input_path, output_path);

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
            this->processing(image_path_string, output_path_full_string);
            log_file << output_path_full_string << endl;
          }
        }
      }
      cout << ++count << " " << images_dir << endl;
    }
  }
  log_file.close();
}

Base::Base(char** argv) {
  this->argv = argv;
}

