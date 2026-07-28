# vhliboptimal_test

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![CMake](https://img.shields.io/badge/Build-CMake-1f4f9c.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Cross--platform-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Version](https://img.shields.io/badge/Version-0.0.3--beta-orange.svg)
![Author](https://img.shields.io/badge/Author-V01G04A81-brown.svg)


### Test suite for shape contour detection and image outline recognition

Dependencies:
* vhliboptimal 0.7.5-beta (optimization in progress; approximately 70% complete)
https://github.com/vigatron/vhliboptimal


##### Example 1: Image size: 4096*4096 Letters and Geometric shape (Extreme Size Test)

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

##### Example 2: Image size: 4096*4096 Letters and Geometric shape (Extreme Size Test)

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

##### Example 3: Image size: 1920*1080 (1080p) Shapes (Default)

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

##### Example 4: Image size: 1920*1080 (1080p) Synthetic Dense Text Block (Extreme Stress Test)

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


### Benchmark Results 2

| Param               | Description |
|---------------------|-------------|
| CPU Model name      | CPU Model name: AMD FX(tm)-8300 Eight-Core Processor |
| Compile Options     | -O3 -mavx -mbmi |
| Pass count          | 16 |


<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage1r4096.jpg | 4096 | 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 6 | 372 | 356 | 424 |
| testimage1r4096.jpg | 4096 | 4096 | 8 | 512 | 512 | 262144 | 32768 | 6 | 139 | 138 | 140 |
| testimage1r4096.jpg | 4096 | 4096 | 16 | 256 | 256 | 65536 | 8192 | 6 | 61 | 61 | 62 |
| testimage1r4096.jpg | 4096 | 4096 | 32 | 128 | 128 | 16384 | 2048 | 6 | 56 | 55 | 60 |

<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage2r4096.jpg | 4096 | 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 3 | 406 | 405 | 407 |
| testimage2r4096.jpg | 4096 | 4096 | 8 | 512 | 512 | 262144 | 32768 | 3 | 108 | 107 | 111 |
| testimage2r4096.jpg | 4096 | 4096 | 16 | 256 | 256 | 65536 | 8192 | 3 | 50 | 50 | 52 |
| testimage2r4096.jpg | 4096 | 4096 | 32 | 128 | 128 | 16384 | 2048 | 3 | 41 | 41 | 43 |

<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage3r1080p.jpg | 1920 | 1080 | 2 | 960 | 540 | 518400 | 64800 | 9 | 123 | 120 | 127 |
| testimage3r1080p.jpg | 1920 | 1080 | 4 | 480 | 270 | 129600 | 16200 | 9 | 30 | 30 | 32 |
| testimage3r1080p.jpg | 1920 | 1080 | 8 | 240 | 135 | 32400 | 4050 | 9 | 10 | 10 | 10 |
| testimage3r1080p.jpg | 1920 | 1080 | 16 | 120 | 68 | 8160 | 1020 | 9 | 4 | 4 | 7 |

<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage4r1080p.jpg | 1920 | 1080 | 1 | 1920 | 1080 | 2073600 | 259200 | 2357 | 10351 | 10320 | 10369 |
| testimage4r1080p.jpg | 1920 | 1080 | 2 | 960 | 540 | 518400 | 64800 | 2141 | 2350 | 2348 | 2365 |


<br>

### Benchmark Results 3

| Param               | Description |
|---------------------|-------------|
| CPU Model name      | Orange Pi PC Plus (Allwinner H3, ARM Cortex-A7, ARMv7-A, 32-bit) |
| Compile Options     | -O3 -mfpu=neon -mfloat-abi=hard |
| Pass count          | 16 |


<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage1r4096.jpg | 4096 | 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 6 | 2320 | 2317 | 2341 |
| testimage1r4096.jpg | 4096 | 4096 | 8 | 512 | 512 | 262144 | 32768 | 6 | 799 | 798 | 801 |
| testimage1r4096.jpg | 4096 | 4096 | 16 | 256 | 256 | 65536 | 8192 | 6 | 350 | 350 | 352 |
| testimage1r4096.jpg | 4096 | 4096 | 32 | 128 | 128 | 16384 | 2048 | 6 | 217 | 214 | 231 |

<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage2r4096.jpg | 4096 | 4096 | 4 | 1024 | 1024 | 1048576 | 131072 | 3 | 2507 | 2506 | 2510 |
| testimage2r4096.jpg | 4096 | 4096 | 8 | 512 | 512 | 262144 | 32768 | 3 | 650 | 650 | 652 |
| testimage2r4096.jpg | 4096 | 4096 | 16 | 256 | 256 | 65536 | 8192 | 3 | 297 | 297 | 298 |
| testimage2r4096.jpg | 4096 | 4096 | 32 | 128 | 128 | 16384 | 2048 | 3 | 191 | 191 | 192 |


<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage3r1080p.jpg | 1920 | 1080 | 2 | 960 | 540 | 518400 | 64800 | 9 | 788 | 788 | 789 |
| testimage3r1080p.jpg | 1920 | 1080 | 4 | 480 | 270 | 129600 | 16200 | 9 | 198 | 198 | 199 |
| testimage3r1080p.jpg | 1920 | 1080 | 8 | 240 | 135 | 32400 | 4050 | 9 | 66 | 64 | 85 |
| testimage3r1080p.jpg | 1920 | 1080 | 16 | 120 | 68 | 8160 | 1020 | 9 | 30 | 30 | 31 |


<br>

| filename | imageWidth<br>(pixels) | imageHeight<br>(pixels) | cellsize<br>(pixels) | cellsw<br>(cells) | cellsh<br>(cells) | total<br>(cells) | buffsize<br>(bytes) | objects<br>count | tsavg<br>(ms) | tsmin<br>(ms) | tsmax<br>(ms)  |
|----------|------------|-------------|----------|--------|--------|--------|----------|---------|-------|-------|-------|
| testimage4r1080p.jpg | 1920 | 1080 | 1 | 1920 | 1080 | 2073600 | 259200 | 2357 | 58986 | 58977 | 59025 |
| testimage4r1080p.jpg | 1920 | 1080 | 2 | 960 | 540 | 518400 | 64800 | 2141 | 13306 | 13304 | 13312 |

<br>

## Сборка проекта под разные платформы

### Intel i5-1135G7

```bash
mkdir build-intel && cd build-intel
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-intel.cmake ..
make -j$(nproc)
```

### AMD FX-8300

```bash
mkdir build-amd && cd build-amd
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-amd.cmake ..
make -j$(nproc)
```

### Orange Pi PC Plus (ARM Cortex-A7)

```bash
mkdir build-arm && cd build-arm
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-opi-pc-plus.cmake ..
make -j$(nproc)
```


© 2026 V01G04A81 / Viktor Glebov
