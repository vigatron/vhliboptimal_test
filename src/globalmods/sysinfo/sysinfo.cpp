#include "sysinfo.hpp"

#include "version_vhplatform.h"
#include "version_vhlibrle7b.h"
#include "version_vhliboptimal.h"
#include "version_vhliboptimal_test.h"

#include "vhliboptimal.hpp"

#ifdef VHPLATFORM_PC
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <regex>
#endif

#ifdef VHPLATFORM_STM32

#include "main.h"
#include "cmsis_os.h"
#include "sysinfo.hpp"
#include <stdio.h>

// --- Двухэтапный макрос для превращения любого токена в строку ---
#define STRINGIFY_NX(a)         #a
#define STRINGIFY(a)            STRINGIFY_NX(a)

#define BUILD_TARGET_STR        STRINGIFY(BUILD_TARGET_NAME)

/* CMSIS/CubeMX всегда объявляет одно из этих семейств */
#if defined(STM32F0)
    #define MCU_FAMILY "STM32F0"
#elif defined(STM32F1)
    #define MCU_FAMILY "STM32F1"
#elif defined(STM32F2)
    #define MCU_FAMILY "STM32F2"
#elif defined(STM32F3)
    #define MCU_FAMILY "STM32F3"
#elif defined(STM32F4)
    #define MCU_FAMILY "STM32F4"
#elif defined(STM32F7)
    #define MCU_FAMILY "STM32F7"
#elif defined(STM32G0)
    #define MCU_FAMILY "STM32G0"
#elif defined(STM32G4)
    #define MCU_FAMILY "STM32G4"
#elif defined(STM32H7)
    #define MCU_FAMILY "STM32H7"
#elif defined(STM32L0)
    #define MCU_FAMILY "STM32L0"
#elif defined(STM32L4)
    #define MCU_FAMILY "STM32L4"
#elif defined(STM32U5)
    #define MCU_FAMILY "STM32U5"
#else
    #define MCU_FAMILY "STM32 Unknown"
#endif


#endif


#ifdef VHPLATFORM_PC


std::string get_exact_cpu_model()
{
    std::ifstream file("/proc/cpuinfo");
    if (!file.is_open())
    {
        return "Unknown Processor";
    }

    std::string line;
    std::string_view target_key = "model name";

    while (std::getline(file, line))
    {
        if (line.rfind(target_key, 0) == 0)
        {
            size_t colon_pos = line.find(':');
            if (colon_pos != std::string::npos && colon_pos + 2 < line.length())
            {
                std::string full_name = line.substr(colon_pos + 2);

                // Очистка строки от мусора (R), (TM), частоты и т.д.
                full_name = std::regex_replace(full_name, std::regex(R"(\((R|TM|tm)\))"), "");
                full_name = std::regex_replace(full_name, std::regex(R"(\s+CPU\s+@.*)"), "");
                full_name = std::regex_replace(full_name, std::regex(R"(\s+\d+-Core.*)"), "");
                full_name = std::regex_replace(full_name, std::regex(R"(^\s+|\s+$)"), "");

                return full_name;
            }
        }
    }
    return "Unknown CPU Model";
}

#endif


#ifdef VHPLATFORM_STM32

/* Символы линкера для расчета RAM (STM32CubeIDE / GCC) */
extern uint32_t _estack;
extern uint32_t _sdata;


/* Определение суммарного физического объема SRAM по Device ID */
static uint32_t Get_Total_SRAM_KB(uint32_t dev_id)
{
    switch (dev_id) {
        // --- STM32F4 Series ---
        case 0x413: return 192; // F405/415/407/417 (128KB SRAM + 64KB CCM)
        case 0x419: return 256; // F427/437/429/439 (192KB SRAM + 64KB CCM)
        case 0x423: return 320; // F446 (256KB SRAM + 64KB CCM)
        case 0x430: return 128; // F411
        case 0x433: return 96;  // F401xB/C
        case 0x422: return 96;  // F401xD/E
        case 0x441: return 256; // F412

        // --- STM32F1 Series ---
        case 0x412: return 10;  // F103 Low-density
        case 0x410: return 20;  // F103 Medium-density
        case 0x414: return 64;  // F103 High-density
        case 0x434: return 96;  // F103 XL-density (2x512KB flash / 96KB RAM)
        case 0x418: return 64;  // F105/F107 Connectivity line

        // --- STM32F7 Series ---
        case 0x449: return 320; // F745/F746/F756
        case 0x451: return 512; // F765/F767/F769

        // --- STM32H7 Series ---
        case 0x450: return 1024; // H742/743/753/750 (AXI SRAM + DTCM + ITCM + SRAM1..4)
        case 0x480: return 1408; // H723/733/725/735

        default: return 0; // Для неизвестных/нерассмотренных DEV_ID
    }
}


/**
 * 
 */
static void Print_App_Info() {

    printf("\r\n");
    printf("---------------------------------------------------\n");
    printf("Application       : VHLIBOptimal_test\n");
    printf("Platform          : %s @ %d Mhz\n",
        BUILD_TARGET_STR,
        (int) SystemCoreClock / 1000000);
    printf("---------------------------------------------------\n");

}


void Print_STM32_Info(void)
{
    // 1. Считываем Device ID и Revision ID через HAL
    uint32_t dev_id = HAL_GetDEVID();
    uint32_t rev_id = HAL_GetREVID();

    // 2. Считываем Flash через официальный макрос FLASHSIZE_BASE
    // (По адресу FLASHSIZE_BASE лежит 16-битное число — размер в КБ)
    uint16_t flash_kb = *((uint16_t *)FLASHSIZE_BASE);

    // 3. Считываем UID через официальные макросы HAL
    uint32_t uid[3];
    uid[0] = HAL_GetUIDw0();
    uid[1] = HAL_GetUIDw1();
    uid[2] = HAL_GetUIDw2();

    // 4. Main Linker SRAM Size
    uint32_t linker_sram_bytes = (uint32_t)&_estack - (uint32_t)&_sdata;
    uint32_t linker_sram_kb = linker_sram_bytes / 1024;

    // 5. Total Hardware SRAM
    uint32_t total_sram_kb = Get_Total_SRAM_KB(dev_id);
    if (total_sram_kb == 0) {
        total_sram_kb = linker_sram_kb; // Fallback если DEV_ID не занесен в таблицу
    }

    // 6. Output via printf
    printf("\r\n\r\n");
    printf("================ MCU INFO =====================");
    printf("\r\n");
    printf("MCU Family      : %s\r\n", MCU_FAMILY);
    printf("Device ID       : 0x%03X\r\n", (unsigned int)dev_id);
    printf("Revision ID     : 0x%04X\r\n", (unsigned int)rev_id);
    printf("Flash Size      : %u KB\r\n", flash_kb);
    printf("Total RAM       : %u KB\r\n", (unsigned int)total_sram_kb);
    printf("Main SRAM       : %u KB\r\n", (unsigned int)linker_sram_kb);
    printf("Unique ID (UID) : %08X-%08X-%08X\r\n", 
           (unsigned int)uid[0], (unsigned int)uid[1], (unsigned int)uid[2]);
    printf("===============================================");
    printf("\r\n");

}



#endif

/**
 *
 */
static void print_versions() {

    printf("%-20s v%d.%d.%d\n",
           "VHLIB_OPTIMAL_TEST",
           VHAPP_VHLIBOPTIMAL_TEST_VERSION_MAJOR,
           VHAPP_VHLIBOPTIMAL_TEST_VERSION_MINOR,
           VHAPP_VHLIBOPTIMAL_TEST_VERSION_PATCH);

    printf("%-20s %s\n",
        "VHLIB_OPTIMAL",
        vhliboptimal::VHLibOptimal::VersionString());

    printf("%-20s v%d.%d.%d\n",
           "VHLIB_RLE7b",
           VHLIB_RLE7B_VERSION_MAJOR,
           VHLIB_RLE7B_VERSION_MINOR,
           VHLIB_RLE7B_VERSION_PATCH);

}

/**
 *
 */
void VHSYSInfo::SysInfo()
{

    printf("\n*** Application Info\n");
    printf("%-24s: %-20s\n", "Build options", CMAKE_CXX_FLAGS_STR);
    print_versions();

    printf("\n*** System Info ***\n");

    #ifdef VHPLATFORM_PC
    printf("%-24s: %-20s\n", "CPU Model", get_exact_cpu_model().c_str());
    #endif

    #ifdef VHPLATFORM_STM32
    Print_STM32_Info();
    Print_App_Info();
    #endif
    
}

