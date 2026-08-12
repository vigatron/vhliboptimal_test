#include "vhplatform.hpp"
#include "testcontainer.hpp"
// #include "cmsis_os.h"
#include "vhliboptimal.hpp"
#include "vhliboptimal/src/mem/memorylayout.hpp"
#include "callbacks/callbacks.hpp"
#include "sysinfo/sysinfo.hpp"

// Source Image (embedded)
#include "pics/srcimgdata.hpp"


using namespace vhliboptimal;

//
#ifdef VHPLATFORM_PC
#define VHATTR_CCMRAM 
#endif


#ifdef VHPLATFORM_STM32
#define VHATTR_CCMRAM   __attribute__((section(".ccmram")))
#endif


// Buffer for BitFields / CCM RAM dedicated on STM32
VHATTR_CCMRAM static uint8_t    mem_buffer_grid_src     [CFG_MEMSIZE_BYTES_PerGrid];
VHATTR_CCMRAM static uint8_t    mem_buffer_grid_dst     [CFG_MEMSIZE_BYTES_PerGrid];
static uint8_t                  mem_buffer_objects      [CFG_MEMSIZE_BYTES_Objects];
static uint8_t                  mem_buffer_spans        [CFG_MEMSIZE_BYTES_Spans];


/**
 * 
 */
verr TestLibraryContainer::CopyAndScale(uint16_t imageid, uint8_t levelcs) {

    verr resunpack = VHTestImagesArray::unpack(imageid);
    if(vok != resunpack) {
        return verrmsg(101, "Unpack error");
    }

    const uint8_t * pbmp = VHTestImagesArray::TempPtr();
    const BMPFileHeader * pbmphdr = (BMPFileHeader *)pbmp;

    // Transfer source image bitfield
    detector.BitFieldSrc().ClearArea(detector.GetCMatrix());

    // Important
    detector.BMPParserReset();

    // Transfer source image bitfield
    for(uint32_t i = 0; i < pbmphdr->file_size; i++) {
        uint8_t bval = pbmp[i];
        verr r = detector.BMPParserByte(bval, levelcs);
        if(r != vok)
            return verrmsg(105, "Source Image sampling error");
    }

    detector.BitFieldSrc().ClearBorder(detector.GetCMatrix());

    return vok;
}

/**
 * 
 */
verr TestLibraryContainer::TestImage(uint16_t imageid, uint8_t levelcs) {

    CopyAndScale(imageid, levelcs);

    // Exception ?
    verr flagDetectionResults = detector.Run();
    if(flagDetectionResults) {
        return verrmsg(2, "Shape contour detection failed");
    }

    int t_samp_us = tsSampling.result_us();
    arrtsSampling.add(t_samp_us);

    int t_scan_us = tsScanning.result_us();
    arrtsScanning.add(t_scan_us);

    printf("> Sampling: %-10d uSec  Scanning: %-10d uSec \n", t_samp_us, t_scan_us);

    return vok;
}

/**
 * 1. Setup Memory & Callbacks
 * 2. 
 */
verr TestLibraryContainer::StartTests() {

    VHSYSInfo::SysInfo();

    printf("Starting test ...  \n");

    // Check integrity before start & Warmup
    if(VHTestImagesArray::CheckIntegrity())
        return verror(1);

    // Source Images array info
    VHTestImagesArray::CheckResolutions();

    //
    if(VHLIBOptimalSetup()) 
        return verrmsg(2, "VHLIBOptimalSetup() failed");

    // Multiple cycles for average measurements values
    for(int i=0; i < VHLIBOPTIMAL_TEST_PASS_COUNT;i++) {
        uint8_t levelcs = 9 - VHLIB_OPTIMAL_GRID_LX;
        TestImage(i+1, levelcs);
    }

    // GenerateReport(cfg);

    printf("Done!\n");

    return vok;
}

/**
 * 
 */
void TestLibraryContainer::connectCallbackBenchmark(void *userData, int cmd, int param) {

    switch(cmd) {

        case vhliboptimal::eCmdBenchmarkMemalloc:
            break;

        case vhliboptimal::eCmdBenchmarkSampling:
            if(!param) tsSampling.start(); else tsSampling.stop();
            break;

        case vhliboptimal::eCmdBenchmarkScan:
            if(!param)  { tsScanning.start(); }
            else        { tsScanning.stop(); }
            break;

        case vhliboptimal::eCmdBenchmarkSubfuncFigure:
            break;

        default: { }
    }

}

/**
 * 
 */
verr TestLibraryContainer::VHLIBOptimalSetup() {

    //
    vhliboptimal::stConfig cfg = {

        // 
        .spccnt         = 0,

        // Min object size filter
        .min_obj_width  = 2,
        .min_obj_height = 2,

        // Max object size filter
        .max_obj_width  = F1K * 4,
        .max_obj_height = F1K * 4,

        .sortMode       = 0,
        .loglevel       = VHLIB_OPTIMAL_LOG_LEVEL
    };

    const VHMemoryLayout::stMemLayout sMemCfg = {
        .memSrcGrid     = { mem_buffer_grid_src , CFG_MEMSIZE_BYTES_PerGrid },
        .memDstGrid     = { mem_buffer_grid_dst , CFG_MEMSIZE_BYTES_PerGrid },
        .memObject      = { mem_buffer_objects  , CFG_MEMSIZE_BYTES_Objects },
        .memSpans       = { mem_buffer_spans    , CFG_MEMSIZE_BYTES_Spans   }
    };

    verr retsetup = detector.Setup(
        cfg,
        sMemCfg,
        IFACE_OPTIMAL_Border,
        IFACE_OPTIMAL_Content,
        IFACE_OPTIMAL_Benchmark );
    
    if(vok == retsetup) {
        printf("VHLIBOptimal Initialized\n");
    } 
    else {
        return verrmsg(103, "VHLIBOptimal::Setup() failed!");
    }

    // Show Memory layout
    detector.MemoryLayout().ShowMemoryStat();


    // Return initialization status
    return vok;
}


#ifdef __CMT
/**
 * 
 */
verr VHLIBOptimalSetup() {


    return vok;

}


using namespace vhliboptimal;


/**
 * 
 */
verr VHLIBOptimalRun() {

    // Start detection process
    verr flagDetectionResults = detector.Run();
    if(flagDetectionResults) {
        return verrmsg(2, "Shape contour detection failed");
    }
    
    unsigned int timer_clk  = (unsigned int) tsScanning.ResultTick();
    unsigned int timer_us   = timer_clk / (SystemCoreClock / 1000000.0f);

    printf("%-20s : %u\n", "Clocks  elapsed", timer_clk);
    printf("%-20s : %u\n", "Elapsed in uSec", timer_us);

    return vok;
}


#endif


// 2 в степени: вычисление размера ячейки в пикселях
// uint8_t     levelcs; 
// uint8_t levelcs = 1;

// .levelcs        = __builtin_ctz(VHLIB_OPTIMAL_GRID_SZ),
// inline uint8_t FilterLevel() const noexcept { return cfg.minColorVal; }

// Подсветка цветности ячейки
// меньшие значения принимаем за черный
// uint8_t     minColorVal;
// .minColorVal    = VHAPP_OPTIMAL_TEST_FLTVAL,

// const stContainerConfig & cfg
// Memory allocation & Grid settings
// TODO: Check alignment if need 


// 2. Memory allocation
// size_t membytes = detector.CalcMemory();
// asrts(membytes >    1 * F1K, 1, "VHLibOptimal::CalcMemory()");
// asrts(membytes <  512 * F1K, 1, "VHLibOptimal::CalcMemory()");

// Allocate memory with std::vector<uint8_t>
// memBlockAligned.assign(membytes, 0);
// verr r = detector.SetupMemory(memBlockAligned.data(), memBlockAligned.size());
// if(r) return verrmsg(1, "VHLIBOptimalSetup() memory allocation issue");

