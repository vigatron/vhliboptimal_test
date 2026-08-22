#!/bin/sh

# Остановка скрипта при любой ошибке
set -e

export IDF_PATH="$HOME/esp/esp-idf"

. $IDF_PATH/export.sh

idf.py -p /dev/ttyUSB0 flash

idf.py -p /dev/ttyUSB0 monitor
