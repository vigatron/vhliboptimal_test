# vhliboptimal_test

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![CMake](https://img.shields.io/badge/Build-CMake-1f4f9c.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Cross--platform-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Version](https://img.shields.io/badge/Version-0.0.5--beta-orange.svg)
![Author](https://img.shields.io/badge/Author-V01G04A81-brown.svg)



## Test suite for shape contour detection and image outline recognition


### Test Images Examples

* **Example #1:**  Image size: 4096*4096 Letters and Geometric shape (Extreme Size Test)
* **Example #2:**  Image size: 4096*4096 Letters and Geometric shape (Extreme Size Test)
* **Example #3:**  Image size: 1920*1080 (1080p) Shapes
* **Example #4:**  Image size: 1920*1080 (1080p) Synthetic Dense Text Block (Extreme Stress Test)
* **Example #5:**  Image size: 640*480 (VGA) Shapes
* **Example #6:**  Image size: 800*600 (SVGA) Text
* **Example #7:**  Image size: 1280*720 (HD 720p) Shapes & Text


<br>

<table>
  <tr align="center" valign="middle">
    <td>
      <img src="results/testimage1r4096_out.jpg" alt="out" height="200px" width="300px"/>
    </td>
    <td>
      <img src="results/testimage2r4096_out.jpg" alt="out" height="200px" width="300px"/>
    </td>
    <td>
      <img src="results/testimage3r1080p_out.jpg" alt="out" height="200px" width="auto"/>
    </td>
    <td>
      <img src="results/testimage4r1080p_out.jpg" alt="out" height="160px" width="auto"/>
    </td>
    <td>
      <img src="results/testimage5rvga_out.jpg" alt="out" height="160px" width="auto"/>
    </td>
    <td>
      <img src="results/testimage6rsvga_out.jpg" alt="out" height="160px" width="auto"/>
    </td>
    <td>
      <img src="results/testimage7r720p_out.jpg" alt="out" height="160px" width="auto"/>
    </td>
  </tr>
</table>

<br>


<br>

### Tested Platforms

| Platform / Board             | CPU / MCU        | Arch      | Freq      |
|------------------------------|------------------|-----------|-----------|
| ASUS Vivobook                | Intel i5-1135G7  | x86_64    | 2.40 GHz  |
| AMD Based Desktop            | AMD FX-8300      | x86_64    | 3.30 GHz  |
| Orange Pi PC Plus            | ARM Cortex-A7    | ARMv7-A   | 1.20 GHz  |
| Raspberry Pi Model B+ V1.2   | ARM1176JZF-S     | ARMv6     | 700 MHz   |
| CMB32F407HDMIR3              | STM32F407        | Cortex-M4 | 168 MHz   |
| WAVESHARE CORE7XXI           | STM32F746        | Cortex-M7 | 210 MHz   |
| CMB32H750HDMIR1              | STM32H750        | Cortex-M7 | 480 MHz   |

* Planned test: *ESP32 Xtensa LX6 @ 240Mhz*

<br>

#### Benchmark Results rev 0.8.0

* [Benchmark results on Intel i5-1135G7](docs/rev0p8p0/bench_intel_i5-1135G7.txt) |
* [Benchmark results on AMD FX-8300](docs/rev0p8p0/bench_amd_fx8300.txt) |
* [Benchmark results on Orange Pi PC Plus](docs/rev0p8p0/bench_opi_pc_plus.txt) |
* [Benchmark results on Raspberry Pi Model B+ V1.2](docs/rev0p8p0/bench_rpi_modelbplus_v1p2.txt) |
* [Benchmark results on CMB32F407HDMIR3 / STM32F4DISCO](docs/rev0p8p0/bench_cmb32f407hdmir3.txt) |
* [Benchmark results on WaveShare Core7XXI](docs/rev0p8p0/bench_wavesharecore7xxi.txt) |
* [Benchmark results on CMB32H750HDMIR1](docs/rev0p8p0/bench_cmb32h750hdmir1.txt) |

#### Benchmarks Results rev 0.7.5

* [Benchmark on Intel i5-1135G7 @ 2.40GHz](docs/bench/rev0p7p5/bench_intel_i5-1135G7.md)
* [Benchmark on AMD FX-8300 @ 3.30Ghz](docs/bench/rev0p7p5/bench_amd_fx8300.md)
* [Benchmark on Orange PC Plus ARM Cortex-A7 @ 1.2GHz](docs/bench/rev0p7p5/bench_opi_pc_plus.md)

<br>

### Project Sorce code
https://github.com/vigatron/vhliboptimal_test

### Dependencies

* vhlibplatform 0.4.2  
https://github.com/vigatron/vhlibplatform

* vhliboptimal 0.8.0 
https://github.com/vigatron/vhliboptimal

* vhlibrle7b
https://github.com/vigatron/vhlibrle7b


### Build & Run

* [Project compilation for different target platforms](docs/build_and_run.md)

<br>


### Link to resized monochrome .bmp images:  

* [Test Images (#1..#7) with different shapes & text symbols](docs/srcimages.md)


<br>


### Common camera image resolutions

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

#### GRID Configuration / Image Tests

* GRID_512x512        SCALE_LV = 9 (512)
* GRID_256x256        SCALE_LV = 8 (256)
* GRID_128x128        SCALE_LV = 7 (128)

---

© 2026 V01G04A81 / Viktor Glebov
