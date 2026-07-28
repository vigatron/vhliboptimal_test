#!/bin/bash

BUILD_DIR=${BUILD_DIR:-../build}

$BUILD_DIR/test_lib_optimal ../data/testimage1r4096.jpg 4
$BUILD_DIR/test_lib_optimal ../data/testimage1r4096.jpg 8
$BUILD_DIR/test_lib_optimal ../data/testimage1r4096.jpg 16
$BUILD_DIR/test_lib_optimal ../data/testimage1r4096.jpg 32

$BUILD_DIR/test_lib_optimal ../data/testimage2r4096.jpg 4
$BUILD_DIR/test_lib_optimal ../data/testimage2r4096.jpg 8
$BUILD_DIR/test_lib_optimal ../data/testimage2r4096.jpg 16
$BUILD_DIR/test_lib_optimal ../data/testimage2r4096.jpg 32

$BUILD_DIR/test_lib_optimal ../data/testimage3r1080p.jpg 2
$BUILD_DIR/test_lib_optimal ../data/testimage3r1080p.jpg 4
$BUILD_DIR/test_lib_optimal ../data/testimage3r1080p.jpg 8
$BUILD_DIR/test_lib_optimal ../data/testimage3r1080p.jpg 16

$BUILD_DIR/test_lib_optimal ../data/testimage4r1080p.jpg 1
$BUILD_DIR/test_lib_optimal ../data/testimage4r1080p.jpg 2


$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 1
$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 2
$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 4
$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 8
$BUILD_DIR/test_lib_optimal ../data/testimage5rvga.jpg 16

$BUILD_DIR/test_lib_optimal ../data/testimage6rsvga.jpg 1
$BUILD_DIR/test_lib_optimal ../data/testimage6rsvga.jpg 2
$BUILD_DIR/test_lib_optimal ../data/testimage6rsvga.jpg 4
$BUILD_DIR/test_lib_optimal ../data/testimage6rsvga.jpg 8
$BUILD_DIR/test_lib_optimal ../data/testimage6rsvga.jpg 16

$BUILD_DIR/test_lib_optimal ../data/testimage7r720p.jpg 1
$BUILD_DIR/test_lib_optimal ../data/testimage7r720p.jpg 2
$BUILD_DIR/test_lib_optimal ../data/testimage7r720p.jpg 4
$BUILD_DIR/test_lib_optimal ../data/testimage7r720p.jpg 8
$BUILD_DIR/test_lib_optimal ../data/testimage7r720p.jpg 16

