import argparse
import os
from abc import ABCMeta, abstractmethod

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
        '--log_path', default='log.txt', type=str, help='log file path'
    )
    return parser.parse_args()


class Base(metaclass=ABCMeta):
    def __init__(self, args):
        self.args = args
        self.input_paths = []
        self.output_paths = []
        self.count = 1
        # self.log = open(self.args.log_path, 'a')

    def make_directory(self):
        input_path = self.args.input_path
        output_path = self.args.output_path
        for class_dir in os.listdir(input_path):
            class_dir_full = os.path.join(input_path, class_dir)
            for video in os.listdir(class_dir_full):
                video_path = os.path.join(input_path, class_dir, video)
                for image in os.listdir(video_path):
                    image_path = os.path.join(input_path, class_dir, video, image)
                    output_path_full = os.path.join(output_path, class_dir, video, image)
                    self.input_paths.append(image_path)
                    self.output_paths.append(output_path_full)
                output_path_full = os.path.join(output_path, class_dir, video)
                os.makedirs(output_path_full, exist_ok=True)
                print('create {}'.format(output_path_full))

    @abstractmethod
    def process(self, input_path, output_path):
        pass

    def large_data_processing(self):
        Parallel(n_jobs=-1)(
            [delayed(self.process)(self.input_paths[i], self.output_paths[i]) for i in range(len(self.input_paths))])
        # self.log.close()
