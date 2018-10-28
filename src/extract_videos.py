import argparse
import os
import re
import time

from joblib import Parallel, delayed


def parser():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        'input_path', default=None, type=str, help='input path'
    )
    parser.add_argument(
        'output_path', default=None, type=str, help='output path'
    )
    parser.add_argument(
        '--image_frag', default=0, type=int, help='create image flag'
    )
    parser.add_argument(
        '--flow_type', default=0, type=int, help='flow type id'
    )
    parser.add_argument(
        '--fps', default=1, type=int, help='frame rate'
    )
    return parser.parse_args()


class Extract_videos():
    def __init__(self, args):
        self.args = args
        self.flow = {0: 'farn', 1: 'tvl1', 2: 'brox'}
        self.input_video_paths = []
        self.images_paths = []
        self.flow_x_paths = []
        self.flow_y_paths = []
        self.count = 1

    def make_directory(self):
        input_path = self.args.input_path
        output_path = self.args.output_path
        for class_dir in os.listdir(input_path):
            class_dir_full = os.path.join(input_path, class_dir)
            for video in os.listdir(class_dir_full):
                video_path = os.path.join(input_path, class_dir, video)
                video_name = re.sub(r'\.(avi|mkv|mp4|webm)', '', video)
                image_path = os.path.join(output_path, 'images', class_dir, video_name)
                flow_x_path = os.path.join(output_path, 'flow', self.flow[self.args.flow_type], 'flow_x', class_dir,
                                           video_name)
                flow_y_path = os.path.join(output_path, 'flow', self.flow[self.args.flow_type], 'flow_y', class_dir,
                                           video_name)
                if not os.path.isfile(os.path.join(flow_x_path, 'image_00001.jpg')):
                    os.makedirs(image_path, exist_ok=True)
                    os.makedirs(flow_x_path, exist_ok=True)
                    os.makedirs(flow_y_path, exist_ok=True)
                    self.input_video_paths.append(video_path)
                    self.images_paths.append(image_path)
                    self.flow_x_paths.append(flow_x_path)
                    self.flow_y_paths.append(flow_y_path)
                    print('create {}'.format(flow_y_path))

    def process(self, input_video_path, images_path, flow_x_path, flow_y_path):
        file_name = '/image'
        regex = r'([()&;])'
        regex_later = r'\\\1'
        input_video_path = re.sub(regex, regex_later, input_video_path)
        images_path = re.sub(regex, regex_later, images_path)
        flow_x_path = re.sub(regex, regex_later, flow_x_path)
        flow_y_path = re.sub(regex, regex_later, flow_y_path)
        os.system(
            'extract_gpu -f={} -i={} -x={} -y={} -n={} -t={} -o=dir -s={}'.format(input_video_path,
                                                                            images_path + file_name,
                                                                            flow_x_path + file_name,
                                                                            flow_y_path + file_name,
                                                                            self.args.image_frag, self.args.flow_type, self.args.fps))
        print(input_video_path)

    def large_data_processing(self):
        Parallel(n_jobs=-1)(
            [delayed(self.process)(self.input_video_paths[i], self.images_paths[i], self.flow_x_paths[i],
                                   self.flow_y_paths[i]) for i in range(len(self.input_video_paths))])


if __name__ == '__main__':
    extract_videos = Extract_videos(parser())
    extract_videos.make_directory()
    start_time = time.time()
    extract_videos.large_data_processing()
    end_time = time.time() - start_time
    print('Time :{}[sec]'.format(end_time))
