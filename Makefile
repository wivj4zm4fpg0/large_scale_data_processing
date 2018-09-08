canny: src/canny_script.cpp src/make_directory.cpp include/make_directory.h
	g++-7 src/canny_script.cpp src/make_directory.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv` -o bin/canny_script -lstdc++fs

resize: src/resize.cpp src/make_directory.cpp include/make_directory.h
	g++-7 src/resize.cpp src/make_directory.cpp -o bin/image_resize -lstdc++fs

link:
	ln -sf $(PWD)/bin/image_resize ~/bin
	ln -sf $(PWD)/bin/canny_script ~/bin

