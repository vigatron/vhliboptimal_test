#pragma once

#include "platform/platform.hpp"

#include "vhliboptimal.hpp"
#include "log/log.hpp"

#include "timer/vhtimerstamp.hpp"
#include "timer/timeaverager.hpp"

#ifdef VHLIB_OPTIMAL_DEBUG
#define VHLIB_OPTIMAL_LOG_LEVEL 3
#define VHLIB_OPTIMAL_TEST_PASS_COUNT 1
#else
#define VHLIB_OPTIMAL_LOG_LEVEL 1
#endif

// Default pass count
#ifndef VHLIB_OPTIMAL_TEST_PASS_COUNT
#define VHLIB_OPTIMAL_TEST_PASS_COUNT 16
#endif

class TestLibraryContainer
{

public:
    /**
     *
     */
    TestLibraryContainer() = default;

    /**
     *
     */
    verr Init();

    /**
     *
     */
    verr StartTests();

    /**
     *
     */
    static void CALLBACK_VHLIBOPTIMAL_Border(
        void *caller,
        uint8_t cmd,
        uint8_t dirh,
        uint8_t dirv,
        uint16_t cellx,
        uint16_t celly);

    /**
     *
     */
    static void CALLBACK_VHLIBOPTIMAL_Content(
        void *caller,
        uint32_t cell1,
        uint32_t cell2,
        uint8_t dir);

    /**
     *
     */
    static void CALLBACK_VHLIBOPTIMAL_Benchmark(
        void *caller,
        int cmd,
        int param);

private:
    // Global variables
    vhliboptimal::VHLibOptimal detector;

    // Benchmark: sampling related
    TimerAverager arrtsSampling;

    // Benchmark: scan related
    TimerAverager arrtsScanning;

    // Measured when called with callback / IFACE Callbacks
    VHTimerStamp tsSampling;

    // Measured when called with callback / IFACE Callbacks
    VHTimerStamp tsScanning;

    /**
     *
     */
    VHLIB_OPTIMAL_FASTFUNC
    verr CopyAndScale(uint16_t imageid, uint8_t sclevel);

    /**
     *
     */
    verr TestImageAverage(uint16_t imageid, uint8_t levelcs);

    /**
     *
     */
    // VHLIB_OPTIMAL_FASTFUNC
    verr TestImageIteration(uint16_t imageid, uint8_t levelcs);

    /**
     *
     */
    verr CheckResolutions();

    /**
     *
     */
    void CallbackBorder(
        uint8_t cmd,
        uint8_t dirh,
        uint8_t dirv,
        uint16_t cellx,
        uint16_t celly);

    /**
     *
     */
    void CallbackContent(
        uint32_t cell1,
        uint32_t cell2,
        uint8_t dir);

    /**
     *
     */
    void CallbackBenchmark(
        int cmd,
        int param);
};
