### Benchmark Results Orange Pi PC Plus

| Param               | Description |
|---------------------|-------------|
| CPU Model name      | Orange Pi PC Plus (Allwinner H3, ARM Cortex-A7, ARMv7-A, 32-bit) |
| Compile Options     | -O3 -march=native -mfloat-abi=hard -fomit-frame-pointer -flto -funroll-loops |
| Pass count          | 16 |
| vhliboptimal        | ver 0.7.5   |
| vhliboptimal_test   | ver 0.4.0   |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage1r4096.jpg | 4096 x 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 6 | 1301 / 1302 / 1304 |
| testimage1r4096.jpg | 4096 x 4096 | 8 | 512 | 512 | 262144 | 32768 | 6 | 518 / 518 / 519 |
| testimage1r4096.jpg | 4096 x 4096 | 16 | 256 | 256 | 65536 | 8192 | 6 | 292 / 294 / 316 |
| testimage1r4096.jpg | 4096 x 4096 | 32 | 128 | 128 | 16384 | 2048 | 6 | 191 / 191 / 192 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage2r4096.jpg | 4096 x 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 3 | 1421 / 1423 / 1440 |
| testimage2r4096.jpg | 4096 x 4096 | 8 | 512 | 512 | 262144 | 32768 | 3 | 447 / 449 / 456 |
| testimage2r4096.jpg | 4096 x 4096 | 16 | 256 | 256 | 65536 | 8192 | 3 | 259 / 261 / 279 |
| testimage2r4096.jpg | 4096 x 4096 | 32 | 128 | 128 | 16384 | 2048 | 3 | 172 / 172 / 173 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage3r1080p.jpg | 1920 x 1080 | 2 | 960 | 540 | 518400 | 64800 | 9 | 385 / 385 / 386 |
| testimage3r1080p.jpg | 1920 x 1080 | 4 | 480 | 270 | 129600 | 16200 | 9 | 119 / 119 / 119 |
| testimage3r1080p.jpg | 1920 x 1080 | 8 | 240 | 135 | 32400 | 4050 | 9 | 45 / 45 / 45 |
| testimage3r1080p.jpg | 1920 x 1080 | 16 | 120 | 68 | 8160 | 1020 | 9 | 26 / 26 / 27 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage4r1080p.jpg | 1920 x 1080 | 1 | 1920 | 1080 | 2073600 | 259200 | 2357 | 22110 / 22126 / 22175 |
| testimage4r1080p.jpg | 1920 x 1080 | 2 | 960 | 540 | 518400 | 64800 | 2141 | 5033 / 5036 / 5059 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage5rvga.jpg | 640 x 480 | 1 | 640 | 480 | 307200 | 38400 | 12 | 438 / 438 / 439 |
| testimage5rvga.jpg | 640 x 480 | 2 | 320 | 240 | 76800 | 9600 | 12 | 82 / 82 / 83 |
| testimage5rvga.jpg | 640 x 480 | 4 | 160 | 120 | 19200 | 2400 | 12 | 16 / 16 / 17 |
| testimage5rvga.jpg | 640 x 480 | 8 | 80 | 60 | 4800 | 600 | 12 | 6 / 7 / 18 |
| testimage5rvga.jpg | 640 x 480 | 16 | 40 | 30 | 1200 | 150 | 5 | 2 / 2 / 3 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage6rsvga.jpg | 800 x 600 | 1 | 800 | 600 | 480000 | 60000 | 27 | 285 / 285 / 286 |
| testimage6rsvga.jpg | 800 x 600 | 2 | 400 | 300 | 120000 | 15000 | 26 | 68 / 68 / 68 |
| testimage6rsvga.jpg | 800 x 600 | 4 | 200 | 150 | 30000 | 3750 | 26 | 24 / 24 / 25 |
| testimage6rsvga.jpg | 800 x 600 | 8 | 100 | 75 | 7500 | 938 | 26 | 10 / 10 / 11 |
| testimage6rsvga.jpg | 800 x 600 | 16 | 50 | 38 | 1900 | 238 | 18 | 6 / 6 / 6 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage7r720p.jpg | 1280 x 720 | 1 | 1280 | 720 | 921600 | 115200 | 26 | 584 / 584 / 591 |
| testimage7r720p.jpg | 1280 x 720 | 2 | 640 | 360 | 230400 | 28800 | 26 | 135 / 135 / 136 |
| testimage7r720p.jpg | 1280 x 720 | 4 | 320 | 180 | 57600 | 7200 | 26 | 48 / 48 / 49 |
| testimage7r720p.jpg | 1280 x 720 | 8 | 160 | 90 | 14400 | 1800 | 26 | 21 / 21 / 21 |
| testimage7r720p.jpg | 1280 x 720 | 16 | 80 | 45 | 3600 | 450 | 26 | 12 / 12 / 13 |


<br>

*Note: Objects do not disappear at higher cell sizes; some simply merge together due to downsampling.*
