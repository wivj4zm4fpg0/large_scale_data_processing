canny: src/canny.cpp
	g++-7 src/canny.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv` -o bin/canny

resize: src/resize.cpp src/make_directory.cpp include/make_directory.h
	g++-7 src/resize.cpp src/make_directory.cpp -o bin/image_resize -lstdc++fs

canny_processing: src/canny_processing.cpp src/base.cpp include/base.hpp
	g++-7 src/canny_processing.cpp src/base.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv` -o bin/canny_processing -lstdc++fs

resize_processing: src/resize_processing.cpp src/base.cpp include/base.hpp
	g++-7 src/resize_processing.cpp src/base.cpp -o bin/resize_processing -lstdc++fs

extract_videos: src/extract_videos.cpp src/make_directory.cpp include/make_directory.hpp
	g++-7 src/extract_videos.cpp src/make_directory.cpp -o bin/extract_videos -lstdc++fs

gausenoise: src/gausenoise.cpp src/base.cpp include/base.hpp
	g++-7 src/gausenoise.cpp src/base.cpp  `pkg-config --cflags opencv` `pkg-config --libs opencv` -o bin/gausenoise -lstdc++fs

salt_pepper: src/salt_pepper.cpp src/base.cpp include/base.hpp
	g++-7 src/salt_pepper.cpp src/base.cpp  `pkg-config --cflags opencv` `pkg-config --libs opencv` -o bin/salt_pepper -lstdc++fs

link:
	ln -sf $(PWD)/bin/* ~/bin

