#!/bin/sh

# Остановка скрипта при любой ошибке
set -e

. ~/esp/esp-idf/export.sh

script -q -c "idf.py -p /dev/ttyUSB0 monitor" /dev/stdout | col -bx > build/monitor.log
