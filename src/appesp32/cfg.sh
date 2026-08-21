#!/bin/sh

# Остановка скрипта при любой ошибке
set -e

. ~/esp/esp-idf/export.sh

idf.py reconfigure
