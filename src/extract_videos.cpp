#include "../include/make_directory.hpp"

class Extract_videos {
private:
  fs::path input_path;
  fs::path images_path;
  fs::path flow_x_path;
  fs::path flow_y_path;
  fs::path output_path;
  fs::path flow_type;
  string log_path;
  string image_name;
  int image_create_flag;
  int flow_type_id;
public:
  void large_scale_data_processing() {
    fs::path images_path, flow_x_path, flow_y_path, input_path;
    fs::path output_path_full, video_path;
    string output_path_full_string, video_path_string;
    ofstream log_file(this->log_path, ios::app);
    int count = 0;

    if (log_file.is_open() == 0) {
      cout << "Failed to open the file :" << this->log_path << endl;
      exit(1);
    }
    if (this->image_create_flag == 0)   {
      make_directory(this->input_path, this->images_path);
    }
    make_directory(this->input_path, this->flow_x_path);
    make_directory(this->input_path, this->flow_y_path);

    for (auto & class_dir : fs::directory_iterator(this->input_path)) {
      for (auto & video : fs::directory_iterator(class_dir)) {
        video_path = fs::path(video);
        video_path = fs::path(video_path.string().substr(string(this->input_path).length()));
        images_path = this->images_path / video_path;
        flow_x_path = this->flow_x_path / video_path;
        flow_y_path = this->flow_y_path / video_path;
        input_path = this->input_path / video_path;
        if (fs::is_empty(flow_x_path) or fs::is_empty(flow_y_path)) {
          system(("extract_gpu -f=" + input_path.string() + " -i=" + images_path.string() + this->image_name + " -x=" + flow_x_path.string() + this->image_name + " -y=" + flow_y_path.string() + this->image_name + " -o=dir -t=" + to_string(this->flow_type_id) + " -n=" + to_string(this->image_create_flag)).c_str());
          log_file << video_path.string() << endl; 
          cout << ++count << " " << video_path.string() << endl;
        }
      }
    }
    log_file.close();
  }

  Extract_videos(char** argv) {
    this->flow_type_id = stoi(string(argv[4]));
    switch(this->flow_type_id) {
    case 0 :
      flow_type = fs::path("flow/farn");
      break;
    case 1 :
      flow_type = fs::path("flow/tvl1");
      break;
    case 2 :
      flow_type = fs::path("flow/brox");
    }
    this->image_name = "/image";
    fs::path pwd = string(getenv("PWD"));
    this->image_create_flag = stoi(string(argv[5]));
    this->output_path = pwd / fs::path(string(argv[2]));
    this->images_path = output_path / fs::path("images");
    this->flow_x_path = output_path / flow_type / fs::path("flow_x");
    this->flow_y_path = output_path / flow_type / fs::path("flow_y");
    this->input_path = pwd / fs::path(string(argv[1]));
    this->log_path = string(argv[3]);
  }
};

// input path, output path, log_path, optical flow type, image create flag
int main(int argc, char** argv) {
  Extract_videos *extract_videos = new Extract_videos(argv);
  extract_videos->large_scale_data_processing();
  return 0;
}
