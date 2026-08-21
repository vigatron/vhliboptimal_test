#pragma once

#ifdef VHPLATFORM_PC

#include <time.h>

#elif defined(VHPLATFORM_STM32)

#include <cstdint>
#include "main.h"

#elif defined(VHPLATFORM_ESP32)

#include <cstdint>
#include "esp_timer.h"

#else

#error "VHPLATFORM_XXX not specified"

#endif

class VHTimerStamp
{

public:
    VHTimerStamp() = default;

#ifdef VHPLATFORM_STM32
    static void init();
    uint32_t result_ticks();
#endif

#ifdef VHPLATFORM_PC
    long long result_us();
    long long result_ms();
#else
    uint32_t result_us();
    uint32_t result_ms();
#endif


    void start();
    void stop();

private:

#ifdef VHPLATFORM_PC
    struct timespec start_time, end_time;
#endif

#if defined(VHPLATFORM_STM32) || defined(VHPLATFORM_ESP32)
    uint32_t _start;
    uint32_t _stop;
#endif
};
