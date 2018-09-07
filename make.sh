#!/bin/bash -eu

g++-7 $1 `pkg-config --cflags opencv` `pkg-config --libs opencv` -o $(echo $1 | sed -e 's/\.cpp//g') -lstdc++fs

