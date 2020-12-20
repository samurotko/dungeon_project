#!/bin/bash
mkdir build
rm build/* -rf
cd build
cmake ..
make