
### STM32F407 Memory Map

| Segment Name | Start Address | Size | Type / Notes |
| :--- | :--- | :--- | :--- |
| Flash Memory | 0x08000000 | 1 MB | Code and Constants (ICode/DCode) |
| CCM Data RAM | 0x10000000 | 64 KB | Core Coupled (No DMA access) |
| SRAM1 | 0x20000000 | 112 KB | Main System RAM (General purpose) |
| SRAM2 | 0x2001C000 | 16 KB | Auxiliary RAM (Peripheral buffers) |
| Backup SRAM | 0x40024000 | 4 KB | VBAT Powered (Retention RAM) |


**Main SRAM:** 112 KBytes

---

### STM32F746 Memory Map

| Segment Name | Start Address | Size | Type / Notes |
| :--- | :--- | :--- | :--- |
| ITCM Flash | 0x00200000 | 1 MB | Instruction Flash (Max core speed) |
| AXIM Flash | 0x08000000 | 1 MB | Data Flash (System matrix access) |
| ITCM RAM | 0x00000000 | 16 KB | Instruction TCM (0 wait states) |
| DTCM RAM | 0x20000000 | 64 KB | Data TCM (0 wait states, Stack/Heap) |
| SRAM1 | 0x20010000 | 240 KB | Main AXI System RAM |
| SRAM2 | 0x2004C000 | 16 KB | Auxiliary AXI System RAM |
| Backup SRAM | 0x40024000 | 4 KB | VBAT Powered (Retention RAM) |

**Main SRAM:** 240 KBytes

---

### STM32H750 Memory Map

| Segment Name | Start Address | Size | Domain / Notes |
| :--- | :--- | :--- | :--- |
| AXI Flash | 0x08000000 | 128 KB | Bootloader / XIP QSPI Launcher |
| ITCM RAM | 0x00000000 | 64 KB | D1 Domain: Instruction RAM (0 wait) |
| DTCM RAM | 0x20000000 | 128 KB | D1 Domain: Data RAM (0 wait) |
| AXI SRAM | 0x24000000 | 512 KB | D1 Domain: High-perf RAM (Graphics/LTDC) |
| SRAM1 | 0x30000000 | 128 KB | D2 Domain: Peripheral RAM (Ethernet/USB) |
| SRAM2 | 0x30020000 | 128 KB | D2 Domain: Peripheral RAM extension |
| SRAM3 | 0x30040000 | 32 KB | D2 Domain: Networking / Crypto buffers |
| SRAM4 | 0x38000000 | 64 KB | D3 Domain: SmartRun RAM (Low power mode) |
| Backup SRAM | 0x38800000 | 4 KB | D3 Domain: VBAT Powered (Retention RAM) |


**Main SRAM:** 512 KBytes

---

### ESP32-D0WD Memory Map

| Segment Name | Start Address | Size | Type / Notes |
| :--- | :--- | :--- | :--- |
| ROM | 0x40000000 | 448 KB | Bootloader and ROM functions (Read-only) |
| DROM (Data Flash) | 0x3F400000 | up to 16 MB | External SPI Flash mapped as data (via MMU cache) |
| IROM (Code Flash) | 0x400D0000 | up to 16 MB | External SPI Flash mapped as executable code (via MMU) |
| DRAM (Data RAM) | 0x3FF00000 | 320 KB | Internal SRAM (Data bus, heap, `.data`, `.bss`) |
| IRAM (Instruction RAM)| 0x40080000 | 200 KB | Internal SRAM (Instruction bus, ISRs, `IRAM_ATTR`) |
| RTC FAST Memory | 0x3FF80000 / 0x400C0000| 8 KB | PRO CPU only, used for deep sleep wake-up code/data |
| RTC SLOW Memory | 0x50000000 | 8 KB | ULP coprocessor access, data retention during deep sleep |
| PSRAM (Optional) | 0x3F800000 | up to 8 MB | External SPI RAM (mapped via cache, module dependent, e.g., WROVER) |

**Main SRAM:** 520 KBytes (320 KB DRAM + 200 KB IRAM)

*Note:*  
The `D0` index in ESP32-D0WD indicates no embedded flash.  
Code and constants are executed directly from external SPI Flash (XIP) via the hardware MMU and cache.  