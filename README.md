# vhliboptimal_test

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![CMake](https://img.shields.io/badge/Build-CMake-1f4f9c.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Cross--platform-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Version](https://img.shields.io/badge/Version-0.7.2--beta-orange.svg)
![Author](https://img.shields.io/badge/Author-V01G04A81-brown.svg)


## Testing library for shape contour detection and image outline recognition

Dependencies:
* vhliboptimal 0.7.2 https://github.com/vigatron/vhliboptimal


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


### Benchmarks Results 1

CPU Model name: 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz
Compile Options: -O3 -march=native -mavx2 -mbmi
Pass count: 8


File Name: data/testimage1r4096.jpg
Picture Props: W=4096 H=4096, Matrix Props: <cellsw=1024 cellsh=1024> total=1048576 cellsize=4 buffersize=131072 bytes
Found 6 objects
Average: 263 ms/frame


File Name: data/testimage2r4096.jpg
Picture Props: W=4096 H=4096, Matrix Props: <cellsw=1024 cellsh=1024> total=1048576 cellsize=4 buffersize=131072 bytes
Found 3 objects
Average: 142 ms/frame


File Name: data/testimage3r1080p.jpg
Picture Props: W=1920 H=1080, Matrix Props: <cellsw=960 cellsh=540> total=518400 cellsize=2 buffersize=64800 bytes
Found 9 objects
Average: 61 ms/frame


File Name: data/testimage4r1080p.jpg
Picture Props: W=1920 H=1080, Matrix Props: <cellsw=960 cellsh=540> total=518400 cellsize=2 buffersize=64800 bytes
Found 2141 objects
Average: 1193 ms/frame


### Benchmarks Results 2

CPU Model name: AMD FX(tm)-8300 Eight-Core Processor
Compile Options: -O3
Pass count: 8


File Name: data/testimage1r4096.jpg
Picture Props: W=4096 H=4096, Matrix Props: <cellsw=1024 cellsh=1024> total=1048576 cellsize=4 buffersize=131072 bytes
Found 6 objects
Average: 635 ms/frame

File Name: data/testimage2r4096.jpg
Picture Props: W=4096 H=4096, Matrix Props: <cellsw=1024 cellsh=1024> total=1048576 cellsize=4 buffersize=131072 bytes
Found 3 objects
Average: 337 ms/frame

File Name: data/testimage3r1080p.jpg
Picture Props: W=1920 H=1080, Matrix Props: <cellsw=960 cellsh=540> total=518400 cellsize=2 buffersize=64800 bytes
Found 9 objects
Average: 142 ms/frame

File Name: data/testimage4r1080p.jpg
Picture Props: W=1920 H=1080,  Matrix Props: <cellsw=960 cellsh=540> total=518400 cellsize=2 buffer size=64800 bytes
Found 2141 objects
Average: 2586 ms/frame


© 2026 V01G04A81 / Viktor Glebov
