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

    long            tsavg;
    long            tsmin;
    long            tsmax;

};

verr SaveBenchmark(const stBenchmarkParams & bench);
