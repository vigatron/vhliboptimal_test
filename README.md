# vhliboptimal_test

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![CMake](https://img.shields.io/badge/Build-CMake-1f4f9c.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Cross--platform-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Version](https://img.shields.io/badge/Version-0.0.1--beta-orange.svg)
![Author](https://img.shields.io/badge/Author-V01G04A81-brown.svg)


### Test suite for shape contour detection and image outline recognition

Dependencies:
* vhliboptimal 0.7.2-beta (optimization in progress; approximately 33% complete)
https://github.com/vigatron/vhliboptimal


##### Example 1: Image size 4096*4096

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

##### Example 2: Image size 4096*4096

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

##### Example 3: Image size 1920*1080 (1080p)

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

##### Example 4: Image size 1920*1080 (1080p)

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

CPU Model name: 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz
Compile Options: -O3 -march=native -mavx2 -mbmi
Pass count: 8

##### Example 1

File Name: data/testimage1r4096.jpg
Image Props: W=4096 H=4096, Matrix Props: <cellsw=1024 cellsh=1024> total=1048576 cellsize=4 buffersize=131072 bytes
Found 6 objects
Average: 263 ms/frame

File Name: ../data/testimage1r4096.jpg
Image Props: W=4096 H=4096, Matrix Props: <cellsw=512 cellsh=512> total=262144 cellsize=8 buffersize=32768 bytes
Found 6 objects
Average: 85 ms/frame

File Name: ../data/testimage1r4096.jpg
Image Props: W=4096 H=4096, Matrix Props: <cellsw=256 cellsh=256> total=65536 cellsize=16 buffersize=8192 bytes
Found 6 objects
Average: 20 ms/frame

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

CPU Model name: AMD FX(tm)-8300 Eight-Core Processor
Compile Options: -O3
Pass count: 8

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


© 2026 V01G04A81 / Viktor Glebov
