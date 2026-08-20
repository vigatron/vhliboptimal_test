### Benchmark Results Intel(R) i5-1135G7

| Param               | Description |
|---------------------|-------------|
| CPU Model name      | 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz |
| Compile Options     | -O3 -march=native -flto -funroll-loops |
| Pass count          | 16 |
| vhliboptimal        | ver 0.7.5   |
| vhliboptimal_test   | ver 0.4.0   |

<br>

| File Name |imgWidth / imgHeight<br>(pixels) |CellSize<br>(pixels) |CellsW * CellsH = CellsT<br>(cells) |Buff Size<br>(bytes) |Objects<br>count |Sampling (ms)<br>tsmin / tsavg / tsmax |Scanning (ms)<br>tsmin / tsavg / tsmax |Total (ms)   <br>tsmin / tsavg / tsmax |
|---|---|---|---|---|---|---|---|---|
| testimage1r4096.jpg |4096 x 4096 |4 |1024 * 1024 = 1048576 |131072 |6 |37 / 37 / 38 |40 / 40 / 40 |77 / 77 / 78 |
| testimage1r4096.jpg |4096 x 4096 |8 |512 * 512 = 262144 |32768 |6 |20 / 20 / 20 |9 / 9 / 9 |29 / 29 / 29 |
| testimage1r4096.jpg |4096 x 4096 |16 |256 * 256 = 65536 |8192 |6 |10 / 10 / 10 |1 / 1 / 2 |11 / 11 / 12 |
| testimage1r4096.jpg |4096 x 4096 |32 |128 * 128 = 16384 |2048 |6 |6 / 6 / 6 |<1 / <1 / <1 |6 / 6 / 6 |

<br>

| File Name |imgWidth / imgHeight<br>(pixels) |CellSize<br>(pixels) |CellsW * CellsH = CellsT<br>(cells) |Buff Size<br>(bytes) |Objects<br>count |Sampling (ms)<br>tsmin / tsavg / tsmax |Scanning (ms)<br>tsmin / tsavg / tsmax |Total (ms)   <br>tsmin / tsavg / tsmax |
|---|---|---|---|---|---|---|---|---|
| testimage2r4096.jpg |4096 x 4096 |4 |1024 * 1024 = 1048576 |131072 |3 |35 / 35 / 35 |48 / 48 / 48 |83 / 83 / 83 |
| testimage2r4096.jpg |4096 x 4096 |8 |512 * 512 = 262144 |32768 |3 |18 / 18 / 19 |6 / 6 / 6 |24 / 24 / 25 |
| testimage2r4096.jpg |4096 x 4096 |16 |256 * 256 = 65536 |8192 |3 |9 / 9 / 10 |1 / 1 / 1 |10 / 10 / 11 |
| testimage2r4096.jpg |4096 x 4096 |32 |128 * 128 = 16384 |2048 |3 |5 / 5 / 6 |<1 / <1 / <1 |5 / 5 / 6 |

<br>

| File Name |imgWidth / imgHeight<br>(pixels) |CellSize<br>(pixels) |CellsW * CellsH = CellsT<br>(cells) |Buff Size<br>(bytes) |Objects<br>count |Sampling (ms)<br>tsmin / tsavg / tsmax |Scanning (ms)<br>tsmin / tsavg / tsmax |Total (ms)   <br>tsmin / tsavg / tsmax |
|---|---|---|---|---|---|---|---|---|
| testimage3r1080p.jpg |1920 x 1080 |2 |960 * 540 = 518400 |64800 |9 |8 / 8 / 9 |16 / 16 / 16 |24 / 24 / 25 |
| testimage3r1080p.jpg |1920 x 1080 |4 |480 * 270 = 129600 |16200 |9 |4 / 4 / 4 |3 / 3 / 3 |7 / 7 / 7 |
| testimage3r1080p.jpg |1920 x 1080 |8 |240 * 135 = 32400 |4050 |9 |2 / 2 / 2 |<1 / <1 / <1 |2 / 2 / 2 |
| testimage3r1080p.jpg |1920 x 1080 |16 |120 * 68 = 8160 |1020 |9 |1 / 1 / 1 |<1 / <1 / <1 |1 / 1 / 1 |

<br>

| File Name |imgWidth / imgHeight<br>(pixels) |CellSize<br>(pixels) |CellsW * CellsH = CellsT<br>(cells) |Buff Size<br>(bytes) |Objects<br>count |Sampling (ms)<br>tsmin / tsavg / tsmax |Scanning (ms)<br>tsmin / tsavg / tsmax |Total (ms)   <br>tsmin / tsavg / tsmax |
|---|---|---|---|---|---|---|---|---|
| testimage4r1080p.jpg |1920 x 1080 |1 |1920 * 1080 = 2073600 |259200 |2357 |19 / 19 / 20 |1368 / 1368 / 1369 |1387 / 1387 / 1389 |
| testimage4r1080p.jpg |1920 x 1080 |2 |960 * 540 = 518400 |64800 |2141 |9 / 9 / 10 |307 / 307 / 308 |316 / 316 / 318 |

<br>

| File Name |imgWidth / imgHeight<br>(pixels) |CellSize<br>(pixels) |CellsW * CellsH = CellsT<br>(cells) |Buff Size<br>(bytes) |Objects<br>count |Sampling (ms)<br>tsmin / tsavg / tsmax |Scanning (ms)<br>tsmin / tsavg / tsmax |Total (ms)   <br>tsmin / tsavg / tsmax |
|---|---|---|---|---|---|---|---|---|
| testimage5rvga.jpg |640 x 480 |1 |640 * 480 = 307200 |38400 |12 |2 / 2 / 3 |25 / 25 / 26 |27 / 27 / 29 |
| testimage5rvga.jpg |640 x 480 |2 |320 * 240 = 76800 |9600 |12 |1 / 1 / 1 |4 / 4 / 4 |5 / 5 / 5 |
| testimage5rvga.jpg |640 x 480 |4 |160 * 120 = 19200 |2400 |12 |<1 / <1 / <1 |<1 / <1 / <1 |<1 / <1 / <1 |
| testimage5rvga.jpg |640 x 480 |8 |80 * 60 = 4800 |600 |12 |<1 / <1 / <1 |<1 / <1 / <1 |<1 / <1 / <1 |
| testimage5rvga.jpg |640 x 480 |16 |40 * 30 = 1200 |150 |5 |<1 / <1 / <1 |<1 / <1 / <1 |<1 / <1 / <1 |


<br>

| File Name |imgWidth / imgHeight<br>(pixels) |CellSize<br>(pixels) |CellsW * CellsH = CellsT<br>(cells) |Buff Size<br>(bytes) |Objects<br>count |Sampling (ms)<br>tsmin / tsavg / tsmax |Scanning (ms)<br>tsmin / tsavg / tsmax |Total (ms)   <br>tsmin / tsavg / tsmax |
|---|---|---|---|---|---|---|---|---|
| testimage6rsvga.jpg |800 x 600 |1 |800 * 600 = 480000 |60000 |27 |4 / 4 / 4 |13 / 13 / 15 |17 / 17 / 19 |
| testimage6rsvga.jpg |800 x 600 |2 |400 * 300 = 120000 |15000 |26 |2 / 2 / 2 |2 / 2 / 2 |4 / 4 / 4 |
| testimage6rsvga.jpg |800 x 600 |4 |200 * 150 = 30000 |3750 |26 |1 / 1 / 1 |<1 / <1 / <1 |1 / 1 / 1 |
| testimage6rsvga.jpg |800 x 600 |8 |100 * 75 = 7500 |938 |26 |<1 / <1 / <1 |<1 / <1 / <1 |<1 / <1 / <1 |
| testimage6rsvga.jpg |800 x 600 |16 |50 * 38 = 1900 |238 |18 |<1 / <1 / <1 |<1 / <1 / <1 |<1 / <1 / <1 |


<br>

| File Name |imgWidth / imgHeight<br>(pixels) |CellSize<br>(pixels) |CellsW * CellsH = CellsT<br>(cells) |Buff Size<br>(bytes) |Objects<br>count |Sampling (ms)<br>tsmin / tsavg / tsmax |Scanning (ms)<br>tsmin / tsavg / tsmax |Total (ms)   <br>tsmin / tsavg / tsmax |
|---|---|---|---|---|---|---|---|---|
| testimage7r720p.jpg |1280 x 720 |1 |1280 * 720 = 921600 |115200 |26 |8 / 8 / 8 |28 / 28 / 29 |36 / 36 / 37 |
| testimage7r720p.jpg |1280 x 720 |2 |640 * 360 = 230400 |28800 |26 |4 / 4 / 4 |4 / 4 / 5 |8 / 8 / 9 |
| testimage7r720p.jpg |1280 x 720 |4 |320 * 180 = 57600 |7200 |26 |1 / 1 / 2 |<1 / <1 / 1 |1 / 1 / 3 |
| testimage7r720p.jpg |1280 x 720 |8 |160 * 90 = 14400 |1800 |26 |1 / 1 / 1 |<1 / <1 / <1 |1 / 1 / 1 |
| testimage7r720p.jpg |1280 x 720 |16 |80 * 45 = 3600 |450 |26 |<1 / <1 / <1 |<1 / <1 / <1 |<1 / <1 / <1 |
