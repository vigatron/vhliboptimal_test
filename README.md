# vhliboptimal_test

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![CMake](https://img.shields.io/badge/Build-CMake-1f4f9c.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Cross--platform-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Version](https://img.shields.io/badge/Version-0.0.2--beta-orange.svg)
![Version](https://img.shields.io/badge/Version-0.0.2--beta-orange.svg)
![Author](https://img.shields.io/badge/Author-V01G04A81-brown.svg)


### Test suite for shape contour detection and image outline recognition

Dependencies:
* vhliboptimal 0.7.5-beta (optimization in progress; approximately 70% complete)
https://github.com/vigatron/vhliboptimal


##### Example 1: Image size 4096*4096 Letters and Geometric shape

<table>
  <tr>
    <td align="center">
      <img src="data/testimage1r4096.jpg" alt="src" style="width:100%; height:auto;"/>
    </td>
    <td align="center">
      <img src="results/testimage1r4096_out.jpg" alt="out" style="width:100%; height:auto;"/>
    </td>
  </tr>
</table>

##### Example 2: Image size 4096*4096 Letters and Geometric shape

<table>
  <tr>
    <td align="center">
      <img src="data/testimage2r4096.jpg" alt="src" style="width:100%; height:auto;"/>
    </td>
    <td align="center">
      <img src="results/testimage2r4096_out.jpg" alt="out" style="width:100%; height:auto;"/>
    </td>
  </tr>
</table>

##### Example 3: Image size 1920*1080 (1080p) Shapes

<table>
  <tr>
    <td align="center">
      <img src="data/testimage3r1080p.jpg" alt="src" style="width:100%; height:auto;"/>
    </td>
    <td align="center">
      <img src="results/testimage3r1080p_out.jpg" alt="out" style="width:100%; height:auto;"/>
    </td>
  </tr>
</table>

##### Example 4: Image size 1920*1080 (1080p) Text Block

<table>
  <tr>
    <td align="center">
      <img src="data/testimage4r1080p.jpg" alt="src" style="width:100%; height:auto;"/>
    </td>
    <td align="center">
      <img src="results/testimage4r1080p_out.jpg" alt="out" style="width:100%; height:auto;"/>
    </td>
  </tr>
</table>


### Benchmark Results 1

| Param               | Description |
|---------------------|-------------|
| CPU Model name      | 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz |
| Compile Options     | -O3 -march=native -mavx2 -mbmi |
| Pass count          | 16 |

<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage1r4096.jpg | 4096 | 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 6 | 160 | 160 | 162 |
| testimage1r4096.jpg | 4096 | 4096 | 8 | 512 | 512 | 262144 | 32768 | 6 | 56 | 56 | 57 |
| testimage1r4096.jpg | 4096 | 4096 | 16 | 256 | 256 | 65536 | 8192 | 6 | 21 | 21 | 21 |
| testimage1r4096.jpg | 4096 | 4096 | 32 | 128 | 128 | 16384 | 2048 | 6 | 14 | 14 | 15 |

<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage2r4096.jpg | 4096 | 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 3 | 173 | 172 | 174 |
| testimage2r4096.jpg | 4096 | 4096 | 8 | 512 | 512 | 262144 | 32768 | 3 | 46 | 46 | 47 |
| testimage2r4096.jpg | 4096 | 4096 | 16 | 256 | 256 | 65536 | 8192 | 3 | 17 | 17 | 17 |
| testimage2r4096.jpg | 4096 | 4096 | 32 | 128 | 128 | 16384 | 2048 | 3 | 12 | 12 | 13 |

<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage3r1080p.jpg | 1920 | 1080 | 2 | 960 | 540 | 518400 | 64800 | 9 | 52 | 52 | 54 |
| testimage3r1080p.jpg | 1920 | 1080 | 4 | 480 | 270 | 129600 | 16200 | 9 | 14 | 14 | 15 |
| testimage3r1080p.jpg | 1920 | 1080 | 8 | 240 | 135 | 32400 | 4050 | 9 | 4 | 4 | 5 |
| testimage3r1080p.jpg | 1920 | 1080 | 16 | 120 | 68 | 8160 | 1020 | 9 | 1 | 1 | 2 |

<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage4r1080p.jpg | 1920 | 1080 | 1 | 1920 | 1080 | 2073600 | 259200 | 2357 | 3625 | 3619 | 3633 |
| testimage4r1080p.jpg | 1920 | 1080 | 2 | 960 | 540 | 518400 | 64800 | 2141 | 819 | 812 | 825 |

<br>

##### Example 2

File Name: data/testimage2r4096.jpg
Image Props: W=4096 H=4096, Matrix Props: <cellsw=1024 cellsh=1024> total=1048576 cellsize=4 buffersize=131072 bytes
Found 3 objects
Average: 142 ms/frame

File Name: data/testimage2r4096.jpg
Image Props: W=4096 H=4096, Matrix Props: <cellsw=512 cellsh=512> total=262144 cellsize=8 buffersize=32768 bytes
Found 3 objects
Average: 47 ms/frame

File Name: ../data/testimage2r4096.jpg
Image Props: W=4096 H=4096, Matrix Props: <cellsw=256 cellsh=256> total=65536 cellsize=16 buffersize=8192 bytes
Found 3 objects
Average: 23 ms/frame

##### Example 3

File Name: data/testimage3r1080p.jpg
Image Props: W=1920 H=1080, Matrix Props: <cellsw=960 cellsh=540> total=518400 cellsize=2 buffersize=64800 bytes
Found 9 objects
Average: 61 ms/frame

File Name: ../data/testimage3r1080p.jpg
Image Props: W=1920 H=1080, Matrix Props: <cellsw=480 cellsh=270> total=129600 cellsize=4 buffersize=16200 bytes
Found 9 objects
Average: 18 ms/frame

File Name: ../data/testimage3r1080p.jpg
Image Props: W=1920 H=1080, Matrix Props: <cellsw=240 cellsh=135> total=32400 cellsize=8 buffersize=4050 bytes
Found 9 objects
Average: 5 ms/frame

##### Example 4

File Name: data/testimage4r1080p.jpg
Image Props: W=1920 H=1080, Matrix Props: <cellsw=960 cellsh=540> total=518400 cellsize=2 buffersize=64800 bytes
Found 2141 objects
Average: 1193 ms/frame


### Benchmark Results 2

| Param               | Description |
|---------------------|-------------|
| CPU Model name      | CPU Model name: AMD FX(tm)-8300 Eight-Core Processor |
| Compile Options     | -O3 -mavx -mbmi |


| Param               | Description |
|---------------------|-------------|
| CPU Model name      | CPU Model name: AMD FX(tm)-8300 Eight-Core Processor |
| Compile Options     | -O3 -mavx -mbmi |


Compile Options: -O3



##### Example 1

File Name: data/testimage1r4096.jpg
Image Props: W=4096 H=4096, Matrix Props: <cellsw=1024 cellsh=1024> total=1048576 cellsize=4 buffersize=131072 bytes
Found 6 objects
Average: 635 ms/frame

##### Example 2

File Name: data/testimage2r4096.jpg
Image Props: W=4096 H=4096, Matrix Props: <cellsw=1024 cellsh=1024> total=1048576 cellsize=4 buffersize=131072 bytes
Found 3 objects
Average: 337 ms/frame

##### Example 3

File Name: data/testimage3r1080p.jpg
Image Props: W=1920 H=1080, Matrix Props: <cellsw=960 cellsh=540> total=518400 cellsize=2 buffersize=64800 bytes
Found 9 objects
Average: 142 ms/frame

##### Example 4

File Name: data/testimage4r1080p.jpg
Image Props: W=1920 H=1080,  Matrix Props: <cellsw=960 cellsh=540> total=518400 cellsize=2 buffersize=64800 bytes
Found 2141 objects
Average: 2586 ms/frame


# New Test


| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | pass<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage3r1080p.jpg | 1920 | 1080 | 4 | 480 | 270 | 129600 | 16200 | 16 | 17 | 17 | 18 |

# New Test


| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | pass<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage3r1080p.jpg | 1920 | 1080 | 4 | 480 | 270 | 129600 | 16200 | 16 | 17 | 17 | 18 |

© 2026 V01G04A81 / Viktor Glebov
