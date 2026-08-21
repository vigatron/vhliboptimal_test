#!/bin/sh

# Остановка скрипта при любой ошибке
set -e

. ~/esp/esp-idf/export.sh

idf.py -p /dev/ttyUSB0 flash

idf.py -p /dev/ttyUSB0 monitor --output-file build/monitor.log
