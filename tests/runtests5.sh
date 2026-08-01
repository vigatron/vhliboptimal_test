#!/bin/bash

rm -f *.md
rm -f *.jpg

BUILD_DIR=${BUILD_DIR:-../build-intel}



$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 1
$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 2
$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 4
$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 8
$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 16

