#pragma once

#include "vhplatform.hpp"


struct stBenchmarkParams {

    std::string     filename;
    int             imageWidth;
    int             imageHeight;

    int             cellsize;

    int             cellsw;
    int             cellsh;
    int             cellst;
    int             buffsize;

    int             objscnt;

    // Sampling
    long            ts_smp_min;
    long            ts_smp_avg;
    long            ts_smp_max;

    // Scanning
    long            ts_scn_min;
    long            ts_scn_avg;
    long            ts_scn_max;

    // Total
    long            ts_fin_min;
    long            ts_fin_avg;
    long            ts_fin_max;

};

class TSArray {

    public:

        TSArray() : idx(0), summ(0) {
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

        int resultmin() { return min; }
        int result()    { return summ / passes_count; }
        int resultmax() { return max; }

    private:
        static constexpr int passes_count = VHLIBOPTIMAL_TEST_PASS_COUNT;

        int     idx;
        long    summ;
        int     min;
        int     max;
};


verr SaveBenchmark(const stBenchmarkParams & bench);
