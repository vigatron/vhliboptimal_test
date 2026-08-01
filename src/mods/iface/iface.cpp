#include "vhplatform.hpp"
#include "vhliboptimal.hpp"

#include "vhtimerstamp.hpp"
#include "benchmark.hpp"

#include <QImage>

using namespace vhliboptimal;


TimerStamp  tsSampling;
TimerStamp  tsScanning;

/**
 * 
 */
void IFACE_OPTIMAL_Border(
    void *userData,
    uint8_t cmd,
    uint8_t dirh, 
    uint8_t dirv,
    uint16_t cellx,
    uint16_t celly, 
    uint16_t imgx,
    uint16_t imgy
) {

}

/**
 * 
 */
void IFACE_OPTIMAL_Content(
    void *userData,
    uint32_t cell1,
    uint32_t cell2,
    uint8_t dir
) {

}

/**
 * 
 */
void IFACE_OPTIMAL_Benchmark(
    void *userData,
    int cmd,
    int param
) {

    switch(cmd) {

        case eCmdBenchmarkMemalloc:
            break;

        case eCmdBenchmarkSampling:
            if(!param) tsSampling.start(); else tsSampling.stop();
            break;

        case eCmdBenchmarkScan:
            if(!param) tsScanning.start(); else tsScanning.stop();
            break;

        case eCmdBenchmarkSubfuncFigure:
            break;

        default: { }
    }
}