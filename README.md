# vhliboptimal_test

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![CMake](https://img.shields.io/badge/Build-CMake-1f4f9c.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Cross--platform-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Version](https://img.shields.io/badge/Version-0.0.5--beta-orange.svg)
![Author](https://img.shields.io/badge/Author-V01G04A81-brown.svg)



## Test suite for shape contour detection and image outline recognition

---

#### Dependencies


* vhlibplatform 0.4.2  
https://github.com/vigatron/vhlibplatform

* vhliboptimal 0.8.0-beta (optimization in progress)  
https://github.com/vigatron/vhliboptimal


<br>

#### Project Sorce code
https://github.com/vigatron/vhliboptimal_test

<br>

#### Benchmark Results rev 0.8.0

* [Benchmark on Intel i5-1135G7 @ 2.40GHz](docs/rev0p8p0/bench_intel_i5-1135G7.md)
* [Benchmark on AMD FX-8300 @ 3.30Ghz](docs/rev0p8p0/bench_amd_fx8300.md)
* [Benchmark on Orange PC Plus ARM Cortex-A7](docs/rev0p8p0/bench_opi_pc_plus.md)
* [Benchmark on CMB32F407HDM (or STM32F4DISCO) STM32F407 @ 160Mhz](docs/rev0p8p0/bench_cmb32f407hdm.md)
* [Benchmark on WaveShare Core7XXI STM32F746 @ 216Mhz](docs/rev0p8p0/bench_wavesharecore7xxi.md)
* [Benchmark on CMB32H750HDM STM32H750 @ 480Mhz](docs/rev0p8p0/bench_cmb32h750hdm.md)

#### Benchmarks Results rev 0.7.5
* [Benchmark on Intel i5-1135G7 @ 2.40GHz](docs/bench/rev0p7p5/bench_intel_i5-1135G7.md)
* [Benchmark on AMD FX-8300 @ 3.30Ghz](docs/bench/rev0p7p5/bench_amd_fx8300.md)
* [Benchmark on Orange PC Plus ARM Cortex-A7](docs/bench/rev0p7p5/bench_opi_pc_plus.md)

#### Build & Run

* [Project compilation for different target platforms](docs/build_and_run.md)

<br>

#### Test Images Examples

* **Example #1:**  Image size: 4096*4096 Letters and Geometric shape (Extreme Size Test)
* **Example #2:**  Image size: 4096*4096 Letters and Geometric shape (Extreme Size Test)
* **Example #3:**  Image size: 1920*1080 (1080p) Shapes
* **Example #4:**  Image size: 1920*1080 (1080p) Synthetic Dense Text Block (Extreme Stress Test)
* **Example #5:**  Image size: 640*480 (VGA) Shapes
* **Example #6:**  Image size: 800*600 (SVGA) Text
* **Example #7:**  Image size: 1280*720 (HD 720p) Shapes & Text


Link to original jpg and resized bmp images:  

* [Test Images (#1..#7) with different shapes & text symbols](docs/srcimages.md)


<br>


#### Common camera image resolutions

| Name      | Resolution      | Aspect ratio |
|-----------|-----------------|--------------|
| VGA       | 640 × 480       | 4:3          |
| SVGA      | 800 × 600       | 4:3          |
| XGA       | 1024 × 768      | 4:3          |
| HD 720p   | 1280 × 720      | 16:9         |
| SXGA      | 1280 × 1024     | 5:4          |
| UXGA      | 1600 × 1200     | 4:3          |
| FHD 1080p | 1920 × 1080     | 16:9         |
| QSXGA     | 2592 × 1944     | 4:3          |
| 4K UHD    | 3840 × 2160     | 16:9         |

---

### Embedded Images Tests - 

Original            1       2       3       4       5       6       7

GRID_512x512        512
GRID_256x256        256
GRID_128x128        128



example1.vhrle > example1.bmp   512x512     > 512 (8:8 / 1:1) > 256 (16:16 / 2:2) > 128 (32:32 / 4:4)
example2.vhrle > example1.bmp   512x512
example3.vhrle > example1.bmp   ? x ?
example4.vhrle > example1.bmp   ? x ?
example5.vhrle > example1.bmp   ? x ?
example6.vhrle > example1.bmp   ? x ?
example7.vhrle > example1.bmp   ? x ?

---

© 2026 V01G04A81 / Viktor Glebov
