#!/bin/bash

../build/test_lib_optimal ../data/testimage1r4096.jpg 4
../build/test_lib_optimal ../data/testimage1r4096.jpg 8
../build/test_lib_optimal ../data/testimage1r4096.jpg 16
../build/test_lib_optimal ../data/testimage1r4096.jpg 32

../build/test_lib_optimal ../data/testimage2r4096.jpg 4
../build/test_lib_optimal ../data/testimage2r4096.jpg 8
../build/test_lib_optimal ../data/testimage2r4096.jpg 16
../build/test_lib_optimal ../data/testimage2r4096.jpg 32

../build/test_lib_optimal ../data/testimage3r1080p.jpg 2
../build/test_lib_optimal ../data/testimage3r1080p.jpg 4
../build/test_lib_optimal ../data/testimage3r1080p.jpg 8
../build/test_lib_optimal ../data/testimage3r1080p.jpg 16

../build/test_lib_optimal ../data/testimage4r1080p.jpg 1
../build/test_lib_optimal ../data/testimage4r1080p.jpg 2
