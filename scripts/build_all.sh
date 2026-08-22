#!/bin/sh

# Остановка скрипта при любой ошибке
set -e

./build_native.sh

./build_cmb32f407hdm.sh

./build_stm32f407disco.sh

./build_wavesharecore7xxi.sh

./build_cmb32h750hdm.sh

./build_esp32d0wd.sh
