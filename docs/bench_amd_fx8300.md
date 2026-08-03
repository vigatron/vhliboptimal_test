### Benchmark Results AMD FX(tm)-8300

| Param               | Description |
|---------------------|-------------|
| CPU Model name      | CPU Model name: AMD FX(tm)-8300 Eight-Core Processor @ 3.30 Ghz |
| Compile Options     | -O3 -march=native -flto -funroll-loops |
| Pass count          | 16 |
| vhliboptimal        | ver 0.7.5   |
| vhliboptimal_test   | ver 0.4.0   |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage1r4096.jpg | 4096 x 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 6 | 183 / 183 / 188 |
| testimage1r4096.jpg | 4096 x 4096 | 8 | 512 | 512 | 262144 | 32768 | 6 | 83 / 84 / 85 |
| testimage1r4096.jpg | 4096 x 4096 | 16 | 256 | 256 | 65536 | 8192 | 6 | 44 / 44 / 46 |
| testimage1r4096.jpg | 4096 x 4096 | 32 | 128 | 128 | 16384 | 2048 | 6 | 26 / 26 / 28 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage2r4096.jpg | 4096 x 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 3 | 195 / 195 / 198 |
| testimage2r4096.jpg | 4096 x 4096 | 8 | 512 | 512 | 262144 | 32768 | 3 | 69 / 69 / 70 |
| testimage2r4096.jpg | 4096 x 4096 | 16 | 256 | 256 | 65536 | 8192 | 3 | 37 / 37 / 38 |
| testimage2r4096.jpg | 4096 x 4096 | 32 | 128 | 128 | 16384 | 2048 | 3 | 25 / 25 / 26 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage3r1080p.jpg | 1920 x 1080 | 2 | 960 | 540 | 518400 | 64800 | 9 | 54 / 54 / 57 |
| testimage3r1080p.jpg | 1920 x 1080 | 4 | 480 | 270 | 129600 | 16200 | 9 | 16 / 16 / 17 |
| testimage3r1080p.jpg | 1920 x 1080 | 8 | 240 | 135 | 32400 | 4050 | 9 | 6 / 6 / 10 |
| testimage3r1080p.jpg | 1920 x 1080 | 16 | 120 | 68 | 8160 | 1020 | 9 | 2 / 2 / 5 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage4r1080p.jpg | 1920 x 1080 | 1 | 1920 | 1080 | 2073600 | 259200 | 2357 | 3282 / 3285 / 3289 |
| testimage4r1080p.jpg | 1920 x 1080 | 2 | 960 | 540 | 518400 | 64800 | 2141 | 751 / 752 / 754 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage5rvga.jpg | 640 x 480 | 1 | 640 | 480 | 307200 | 38400 | 12 | 62 / 62 / 67 |
| testimage5rvga.jpg | 640 x 480 | 2 | 320 | 240 | 76800 | 9600 | 12 | 12 / 12 / 17 |
| testimage5rvga.jpg | 640 x 480 | 4 | 160 | 120 | 19200 | 2400 | 12 | 2 / 2 / 3 |
| testimage5rvga.jpg | 640 x 480 | 8 | 80 | 60 | 4800 | 600 | 12 | 1 / 1 / 2 |
| testimage5rvga.jpg | 640 x 480 | 16 | 40 | 30 | 1200 | 150 | 5 | 0 / 0 / 0 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage6rsvga.jpg | 800 x 600 | 1 | 800 | 600 | 480000 | 60000 | 27 | 40 / 40 / 44 |
| testimage6rsvga.jpg | 800 x 600 | 2 | 400 | 300 | 120000 | 15000 | 26 | 9 / 9 / 13 |
| testimage6rsvga.jpg | 800 x 600 | 4 | 200 | 150 | 30000 | 3750 | 26 | 3 / 3 / 6 |
| testimage6rsvga.jpg | 800 x 600 | 8 | 100 | 75 | 7500 | 938 | 26 | 1 / 1 / 2 |
| testimage6rsvga.jpg | 800 x 600 | 16 | 50 | 38 | 1900 | 238 | 18 | 0 / 0 / 2 |

<br>

| filename | imageWidth / imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsmin / tsavg / tsmax (ms)  |
|----------|----------|----------|----------|----------|----------|----------|----------|----------|
| testimage7r720p.jpg | 1280 x 720 | 1 | 1280 | 720 | 921600 | 115200 | 26 | 82 / 87 / 96 |
| testimage7r720p.jpg | 1280 x 720 | 2 | 640 | 360 | 230400 | 28800 | 26 | 19 / 20 / 23 |
| testimage7r720p.jpg | 1280 x 720 | 4 | 320 | 180 | 57600 | 7200 | 26 | 6 / 6 / 7 |
| testimage7r720p.jpg | 1280 x 720 | 8 | 160 | 90 | 14400 | 1800 | 26 | 2 / 2 / 5 |
| testimage7r720p.jpg | 1280 x 720 | 16 | 80 | 45 | 3600 | 450 | 26 | 1 / 1 / 3 |

<br>
