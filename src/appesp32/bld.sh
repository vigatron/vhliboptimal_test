#!/bin/sh

# Остановка скрипта при любой ошибке
set -e

#
export IDF_PATH="$HOME/esp/esp-idf"

#
. $IDF_PATH/export.sh

#
idf.py -B ../../build-esp32d0wd build

#
idf.py size
