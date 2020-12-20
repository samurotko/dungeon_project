#!/bin/bash
mkdir build
rm build/* -rf
cd build
cmake ..
make
valgrind --leak-check=yes ./rpg