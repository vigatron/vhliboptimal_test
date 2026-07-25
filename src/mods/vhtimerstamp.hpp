#pragma once

#include <time.h>

class TimerStamp {

    public:
        TimerStamp() : elapsed(0) { }
        ~TimerStamp() { }

        void        start()     { clock_gettime(CLOCK_MONOTONIC_RAW, &start_time); }

        void        stop()      { clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);   }

        long long   result_us() {
            elapsed = (end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
            elapsed /= 1000LL;
            return elapsed;
        }

        long long   result_ms() {
            elapsed = (end_time.tv_sec - start_time.tv_sec) * 1000000000LL + (end_time.tv_nsec - start_time.tv_nsec);
            elapsed /= 1000000LL;
            return elapsed;
        }

    private:

        struct timespec     start_time, end_time;
        long long           elapsed;

};
