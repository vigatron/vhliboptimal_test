#include "sysinfo.hpp"

#include "version_vhplatform.h"
#include "version_vhlibrle7b.h"
#include "version_vhliboptimal.h"
#include "version_vhliboptimal_test.h"

#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <regex>

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

/**
 *
 */
void VHSYSInfo::SysInfo()
{

    printf("\n*** Application Info\n");

    printf("%-20s v%d.%d.%d\n",
           "VHLIB_OPTIMAL_TEST",
           VHAPP_VHLIBOPTIMAL_TEST_VERSION_MAJOR,
           VHAPP_VHLIBOPTIMAL_TEST_VERSION_MINOR,
           VHAPP_VHLIBOPTIMAL_TEST_VERSION_PATCH);

    printf("%-20s v%d.%d.%d\n",
           "VHLIB_OPTIMAL",
           VHLIB_OPTIMAL_VERSION_MAJOR,
           VHLIB_OPTIMAL_VERSION_MINOR,
           VHLIB_OPTIMAL_VERSION_PATCH);

    printf("%-20s v%d.%d.%d\n",
           "VHLIB_RLE7b",
           VHLIB_RLE7B_VERSION_MAJOR,
           VHLIB_RLE7B_VERSION_MINOR,
           VHLIB_RLE7B_VERSION_PATCH);


    printf("\n*** System Info ***\n");
    printf("%-24s: %-20s\n", "CPU Model", get_exact_cpu_model().c_str());
    printf("%-24s: %-20s\n", "Build options", CMAKE_CXX_FLAGS_STR);
}