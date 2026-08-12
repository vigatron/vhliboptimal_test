#pragma once

#include <cstdint>

class TimerAverager {

    public:

        TimerAverager() : idx(0), summ(0) {
        }

        void add(int v) {
            if(!idx++) {
                min = v; max = v;
            } else {
                if(v<min) min = v;
                if(v>max) max = v;
            }
            summ += v;
        }

        int resultmin   () const { return min; }
        int resultmax   () const { return max; }
        int result      (int passes_count) const { return summ / passes_count; }

    private:

        int     idx;
        long    summ;
        int     min;
        int     max;
};
