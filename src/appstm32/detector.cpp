#include "vhliboptimal.hpp"
#include "callbacks/callbacks.hpp"
#include "platform/platform.hpp"

//
#include "cmsis_os.h"
#include "benchmark/benchmark.hpp"

// Source Image (embedded)
#include "../pics/srcimgdata.hpp"

#include "vhrle7b.hpp"

using namespace vhliboptimal;

// Переменная или буфер в CCM RAM
__attribute__((section(".ccmram"))) static uint8_t mem_buffer_grid_src[CFG_MEMSIZE_BYTES_PerGrid];
__attribute__((section(".ccmram"))) static uint8_t mem_buffer_grid_dst[CFG_MEMSIZE_BYTES_PerGrid];

static uint8_t mem_buffer_objects  [CFG_MEMSIZE_BYTES_Objects];
static uint8_t mem_buffer_spans    [CFG_MEMSIZE_BYTES_Spans];

VHLibOptimal      detector;

extern VHTimeStamp tsSampling;
extern VHTimeStamp tsScanning;

static const stConfig sCfg = {

    // Misc
    .spccnt         = 0,
    .levelcs        = __builtin_ctz(VHLIB_OPTIMAL_GRID_SZ),
    .minColorVal    = VHAPP_OPTIMAL_TEST_FLTVAL,

    // Min object size filter
    .min_obj_width  = 2,
    .min_obj_height = 2,

    // Max object size filter
    .max_obj_width  = F1K * 4,
    .max_obj_height = F1K * 4,

    .sortMode       = 0,
    .loglevel       = VHLIB_OPTIMAL_LOG_LEVEL

};

static const VHMemoryLayout::stMemLayout sMemCfg = {
    .memSrcGrid     = { mem_buffer_grid_src , CFG_MEMSIZE_BYTES_PerGrid },
    .memDstGrid     = { mem_buffer_grid_dst , CFG_MEMSIZE_BYTES_PerGrid },
    .memObject      = { mem_buffer_objects  , CFG_MEMSIZE_BYTES_Objects },
    .memSpans       = { mem_buffer_spans    , CFG_MEMSIZE_BYTES_Spans   }
};


/**
 * 
 */
verr VHLIBOptimalSetup() {

    verr r = detector.Setup(
        sCfg,
        sMemCfg,
        IFACE_OPTIMAL_Border,
        IFACE_OPTIMAL_Content,
        IFACE_OPTIMAL_Benchmark
    );

    if(r == vok) {
        printf("VHLIBOptimal Initialized\n");
    } 
    else {
        return verrmsg(103, "VHLIBOptimal::Setup() failed!");
    }

    detector.MemoryLayout().ShowMemoryStat();

    return vok;

}

static verr unpack_image(uint16_t imgid) {

    VHRLE7b rle;

    const uint8_t * prle        = VHTestImagesArray::embedded_bmp_data(imgid);
    const uint32_t  blocksz     = VHTestImagesArray::embedded_bmp_size(imgid);
    uint8_t *       ptrdst      = VHTestImagesArray::TempPicPtr();
    uint32_t        sizedst     = VHTestImagesArray::TempPicMaxBufferSize();

    verr testrle = rle.check(prle, blocksz);
    printf("Image #%d check integrity status: %s \n", imgid, testrle ? "FAILED" : "OK");

    if(testrle)
        return testrle;

    verr retunpack = rle.unpack(prle, blocksz, ptrdst, sizedst);
    printf("Image #%d unpack result status: %s \n", imgid, retunpack ? "FAILED" : "OK");

    return retunpack;
}

/**
 * 
 */
verr VHLIBOptimalRun() {

    printf("Starting test ...\n");

    for(uint16_t imgid = 1; imgid <= 7; imgid++) {
        verr vtest = unpack_image(imgid);
        if(vtest) {
            while(1) { osDelay(1); }
        }
    }

    unpack_image(1);

    const uint8_t * pbmp = VHTestImagesArray::TempPicPtr();


    // Transfer source image bitfield
    detector.BitFieldSrc().ClearArea(detector.GetCMatrix());

    detector.BMPParserReset();

    const BMPFileHeader * pbmphdr = (BMPFileHeader *)pbmp;

    for(uint32_t i = 0; i < pbmphdr->file_size; i++) {
        uint8_t bval = pbmp[i];
        verr r = detector.BMPParserByte(bval, sCfg.levelcs);
        if(r != vok) return verrmsg(105, "Source Image sampling error");
    }

    detector.BitFieldSrc().ClearBorder(detector.GetCMatrix());

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