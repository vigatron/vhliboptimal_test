## Project compilation for different target platforms

---
 
Rev 0.8.0
> Will be published ASAP

---

Rev 0.7.5

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
make -j2
```