#include "../include/base_video.hpp"

void Base_Video::large_scale_data_processing() {
  fs::path pwd = string(getenv("PWD"));
  fs::path input_path = pwd / fs::path(this->argv[1]);
  fs::path output_path = pwd / fs::path(this->argv[2]);
  fs::path log_path = fs::path(this->argv[3]);

  fs::path output_path_full, video_path;
  string output_path_full_string, video_path_string;

  ifstream exist_file;
  ofstream log_file(log_path.string(), ios::app);
  int count = 0;

  if (log_file.is_open() == 0) {
    cout << "Failed to open the file :" << log_path.string() << endl;
    exit(1);
  }

  make_directory(images_path, output_path);
  make_directory(flow_x_path, output_path);
  make_directory(flow_y_path, output_path);

  for (auto & class_dir : fs::directory_iterator(input_path)) {
    for (auto & video : fs::directory_iterator(class_dir)) {
      video_path = fs::path(video);
      if (fs::is_empty(video_path)) {
        output_path_full = output_path / video_path.string().substr(string(input_path).length());
        output_path_full_string = output_path_full.string();
        video_path_string = video_path.string();
        this->processing(video_path_string, output_path_full_string);
        log_file << output_path_full_string << endl;
        cout << ++count << " " << video_path_string << endl;
      } else {
        continue;
      }
    }
  }
  log_file.close();
}

Base_Video::Base_Video(char** argv) {
  this->argv = argv;
}

