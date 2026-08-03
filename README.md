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


#### Project Sorce code
https://github.com/vigatron/vhliboptimal_test

#### Benchmark Results rev 0.8.0
* [Benchmark on Intel i5-1135G7 @ 2.40GHz](docs/rev0p8p0/bench_intel_i5-1135G7.md)
* [Benchmark on AMD FX-8300 @ 3.30Ghz](docs/rev0p8p0/bench_amd_fx8300.md)
* [Benchmark on Orange PC Plus ARM Cortex-A7](docs/rev0p8p0/bench_opi_pc_plus.md)

#### Benchmarks Results rev 0.7.5
* [Benchmark on Intel i5-1135G7 @ 2.40GHz](docs/bench/rev0p7p5/bench_intel_i5-1135G7.md)
* [Benchmark on AMD FX-8300 @ 3.30Ghz](docs/bench/rev0p7p5/bench_amd_fx8300.md)
* [Benchmark on Orange PC Plus ARM Cortex-A7](docs/bench/rev0p7p5/bench_opi_pc_plus.md)

#### Build & Run

* [Project compilation for different target platforms](docs/build_and_run.md)


#### Examples

* **Example #1:**  Image size: 4096*4096 Letters and Geometric shape (Extreme Size Test)
* **Example #2:**  Image size: 4096*4096 Letters and Geometric shape (Extreme Size Test)
* **Example #3:**  Image size: 1920*1080 (1080p) Shapes
* **Example #4:**  Image size: 1920*1080 (1080p) Synthetic Dense Text Block (Extreme Stress Test)
* **Example #5:**  Image size: 640*480 (VGA) Shapes
* **Example #6:**  Image size: 800*600 (SVGA) Text
* **Example #7:**  Image size: 1280*720 (HD 720p) Shapes & Text

<br>

<table>
    <tr>
        <td align="left">
        <b>Example #1</b></b><br>
        Original: 4096*4096<br>
        Resized : 512*512<br>
        <img src="data/512/example1.bmp" alt="src" style="width:100%; height:auto;"/>
        <br><br><br>
        </td>
    </tr>
    <tr>
        <td align="left">
        <b>Example #2</b><br>
        Original: 4096*4096<br>
        Resized : 512*512<br>
        <img src="data/512/example2.bmp" alt="src" style="width:100%; height:auto;"/>
        <br><br><br>
        </td>
    </tr>
    <tr>
        <td align="left">
        <b>Example #3</b><br>
        Original: 1920*1080 (1080p)<br>
        Resized : 480*270<br>
        <img src="data/512/example3.bmp" alt="src" style="width:100%; height:auto;"/>
        <br><br><br>
        </td>
    </tr>
    <tr>
        <td align="left">
        <b>Example #4</b><br>
        Original: 1920*1080 (1080p)<br>
        Resized : 480*270<br>
        <img src="data/512/example4.bmp" alt="src" style="width:100%; height:auto;"/>
        <br><br><br>
        </td>
    </tr>
    <tr>
        <td align="left">
        <b>Example #5</b><br>
        Original: 640*480 (VGA)<br>
        Resized : 320*240<br>
        <img src="data/512/example5.bmp" alt="src" style="width:100%; height:auto;"/>
        <br><br><br>
        </td>
    </tr>
    <tr>
        <td align="left">
        <b>Example #6</b><br>
        Original: 800*600 (SVGA)<br>
        Resized : 400*300<br>
        <img src="data/512/example6.bmp" alt="src" style="width:100%; height:auto;"/>
        <br><br><br>
        </td>
    </tr>
    <tr>
        <td align="left">
        <b>Example #7</b><br>
        Original: 1280*720<br>
        Resized : 320*180<br>
        <img src="data/512/example7.bmp" alt="src" style="width:100%; height:auto;"/>
        <br><br><br>
        </td>
    </tr>
  </tr>
</table>


---

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


© 2026 V01G04A81 / Viktor Glebov
