import base
import os


class Canny(base.Base):
    def process(self, input_path, output_path):
        os.system('canny {} {}'.format(input_path, output_path))
        log_str = '{} {}'.format(self.count, output_path)
        print(log_str)
        # self.log.write(log_str + '\n')
        self.count = self.count + 1


canny = Canny(base.parser())
canny.make_directory()
print('Go!!')
canny.large_data_processing()
