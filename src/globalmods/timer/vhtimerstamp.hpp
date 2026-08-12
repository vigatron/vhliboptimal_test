#pragma once

#ifdef VHPLATFORM_PC

    #include <time.h>

#elif defined(VHPLATFORM_STM32)

    #include <cstdint>
    #include "main.h"

#else

    #error "VHPLATFORM_XXX not specified"

#endif


class VHTimerStamp {

    public:

        VHTimerStamp();

        void        start();
        void        stop();
        long long   result_us();
        long long   result_ms();

    private:

        struct timespec     start_time, end_time;

};
