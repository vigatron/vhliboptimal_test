#include "vhplatform.hpp"
#include "testcontainer.hpp"
#include "vhliboptimal.hpp"
#include "vhliboptimal/src/mem/memorylayout.hpp"
#include "sysinfo/sysinfo.hpp"

// Source Image (embedded)
#include "pics/srcimgdata.hpp"

namespace vhliboptimal
{
    extern void asrts(bool cond, int module, const char *msg);
};

using namespace vhliboptimal;

// dedicated BitFields GRID Src Buffer @ CCM/DTCM on STM32
VHLIB_OPTIMAL_ALIGNED16 VHLIB_OPTIMAL_FASTSRAM uint8_t mem_buffer_grid_src[CFG_MEMSIZE_BYTES_PerGrid];

// dedicated BitFields GRID Dst Buffer @ CCM/DTCM on STM32
VHLIB_OPTIMAL_ALIGNED16 VHLIB_OPTIMAL_FASTSRAM uint8_t mem_buffer_grid_dst[CFG_MEMSIZE_BYTES_PerGrid];

VHLIB_OPTIMAL_ALIGNED16 static uint8_t mem_buffer_objects[CFG_MEMSIZE_BYTES_Objects];

VHLIB_OPTIMAL_ALIGNED16 static uint8_t mem_buffer_spans[CFG_MEMSIZE_BYTES_Spans];

/**
 *
 */
verr TestLibraryContainer::CopyAndScale(uint16_t imageid, uint8_t levelcs)
{
    // Using spans area as temporary unpacked bitmap buffer
    uint8_t *pbmp = mem_buffer_spans;
    uint16_t pbmp_size = CFG_MEMSIZE_BYTES_Spans;

    // Check output buffer size
    // TODO: compare with uncompressed size / not maximal
    if (pbmp_size < VHTestImagesArray::minRequiredBufferSize())
    {
        return verrmsg(106, "Output bitmap buffer size not enough for CopyAndScale()");
    }

    // Unpack bitmap
    verr resunpack = VHTestImagesArray::unpack(imageid, pbmp, pbmp_size);
    if (vok != resunpack)
    {
        return verrmsg(101, "Unpack error");
    }

    const BMPFileHeader *pbmphdr = (BMPFileHeader *)pbmp;

    // Transfer source image bitfield
    detector.BitFieldSrc().ClearArea(detector.GetCMatrix());

    // Important
    detector.BMPParserReset();

    // Transfer source image bitfield
    for (uint32_t i = 0; i < pbmphdr->file_size; i++)
    {
        uint8_t bval = pbmp[i];
        verr r = detector.BMPParserByte(bval, levelcs);
        if (r != vok)
            return verrmsg(105, "Source Image sampling error");
    }

    return vok;
}

/**
 *
 */
verr TestLibraryContainer::TestImageIteration(uint16_t imageid, uint8_t levelcs)
{

    // Sampling
    tsSampling.start();
    if (vok != CopyAndScale(imageid, levelcs))
        return verrmsg(3, "Scaller error");
    tsSampling.stop();

    // Scanning : Start detection process
    verr flagDetectionResults = detector.Run();
    if (flagDetectionResults)
    {
        return verrmsg(2, "Shape contour detection failed");
    }

    int t_samp_us = tsSampling.result_us();
    arrtsSampling.add(t_samp_us);

    int t_scan_us = tsScanning.result_us();
    arrtsScanning.add(t_scan_us);

    printf(" Sampling: %5d uSec  Scanning: %5d uSec \n", t_samp_us, t_scan_us);

#ifdef __CMT
    printf("%-20s : %u\n", "Clocks  elapsed", timer_clk);
    printf("%-20s : %u\n", "Elapsed in uSec", timer_us);
#endif

    return vok;
}

/**
 * 
 */
verr TestLibraryContainer::CheckResolutions() {

    printf("\nTest image set:\n");

    // Using spans area as temporary unpacked bitmap buffer
    uint8_t *pbmp = mem_buffer_spans;
    uint16_t pbmp_size = CFG_MEMSIZE_BYTES_Spans;

    for(uint16_t blkid = VHTestImagesArray::GetFirstID(); blkid <= VHTestImagesArray::GetLastID(); blkid++) {
        
        int width = 0;
        int height = 0;
        verr result = VHTestImagesArray::unpack(blkid, pbmp, pbmp_size);

        if(result == vok) {
            const uint8_t * pbmphdr = pbmp + sizeof(vhliboptimal::BMPFileHeader);
            const vhliboptimal::BMPInfoHeader * phdr = (vhliboptimal::BMPInfoHeader *)pbmphdr;
            width = phdr->width;
            height = phdr->height;
        }

        uint8_t sc = VHTestImagesArray::GetScaller(blkid);

        printf("BMP (1-bit) B&W Image #%d: %4d x %4d (Original %4d x %4d)\n",
            blkid, width, height, width * sc, height * sc);
    }

    return vok;
}


/**
 *
 */
verr TestLibraryContainer::TestImageAverage(uint16_t imageid, uint8_t levelcs)
{

#ifdef TEST_SHOW_SRC_BITFIELD
    if (vok != CopyAndScale(imageid, levelcs))
        return verrmsg(3, "Scaller error");

    detector.DumpBitfield();
#endif

    arrtsSampling.reset();
    arrtsScanning.reset();

    // Multiple cycles for average measurements values
    for (int i = 0; i < VHLIBOPTIMAL_TEST_PASS_COUNT; i++)
    {
        printf("Iteration %2d of %d: ", i + 1, VHLIBOPTIMAL_TEST_PASS_COUNT);
        TestImageIteration(imageid, levelcs);
    }

    uint16_t objcount = detector.ObjectsCount();
    uint32_t spncount1 = detector.GlobalSpansCount();
    uint32_t spncount2 = detector.CalcSpansTotal();

    log::partout("Found ");
    log::partint(objcount);
    log::partout(" objects");
    log::partout(", Spans ");
    log::partint(spncount1);
    log::partout("( Rnt check ");
    log::partint(spncount2);
    log::lineout(")");

    asrts(spncount1 == spncount2, 100, "Spans Rnt check failed");

    // Sampling
    int ts_smp_min = arrtsSampling.resultmin();
    int ts_smp_avg = arrtsSampling.result(VHLIBOPTIMAL_TEST_PASS_COUNT);
    int ts_smp_max = arrtsSampling.resultmax();

    // Scanning
    int ts_scn_min = arrtsScanning.resultmin();
    int ts_scn_avg = arrtsScanning.result(VHLIBOPTIMAL_TEST_PASS_COUNT);
    int ts_scn_max = arrtsScanning.resultmax();

    // Summ
    int ts_fin_min = ts_smp_min + ts_scn_min;
    int ts_fin_avg = ts_smp_avg + ts_scn_avg;
    int ts_fin_max = ts_smp_max + ts_scn_max;

    // Status
    printf("Sampling (uSec) tsmin / tsavg / tsmax  %6d / %6d / %6d \n", ts_smp_min, ts_smp_avg, ts_smp_max);
    printf("Scanning (uSec) tsmin / tsavg / tsmax  %6d / %6d / %6d \n", ts_scn_min, ts_scn_avg, ts_scn_max);
    printf("Total    (uSec) tsmin / tsavg / tsmax  %6d / %6d / %6d \n", ts_fin_min, ts_fin_avg, ts_fin_max);

    return vok;
}

/**
 * 1. Setup Memory & Callbacks
 * 2.
 */
verr TestLibraryContainer::StartTests()
{
    if (!detector.isInitialized())
        return verrmsg(102, "VHLIB_OPTIMAL is not initialized");

    // Testing all images from embedded set
    uint16_t firstid = VHTestImagesArray::GetFirstID();
    uint16_t lastid = VHTestImagesArray::GetLastID();

    // SCALE Factor
    uint8_t levelcs = 9 - VHLIB_OPTIMAL_GRID_LX;

    for (uint16_t imgid = firstid; imgid <= lastid; imgid++)
    {
        printf("\n*** Testing image #%d of %d\n", imgid, lastid);
        verr vtest = TestImageAverage(imgid, levelcs);
        if (vok != vtest)
            return verrmsg(102, "Test failed");
    }

    // GenerateReport(cfg);

    printf("\nAll tests completed\n");

    return vok;
}

/**
 * Setup memory layout & callbacks
 */
verr TestLibraryContainer::Init()
{
    VHSYSInfo::SysInfo();

    printf("Starting test ...  \n");

    // Check integrity before start & Warmup
    if (VHTestImagesArray::CheckIntegrity())
        return verror(1);

    // Source Images array info
    CheckResolutions();

    //
    vhliboptimal::stConfig cfg = {

        //
        .spccnt = 0,

        // Min object size filter
        .min_obj_width = 2,
        .min_obj_height = 2,

        // Max object size filter
        .max_obj_width = F1K * 4,
        .max_obj_height = F1K * 4,

        .sortMode = 0,
        .loglevel = VHLIB_OPTIMAL_LOG_LEVEL};

    // Memory Layout
    VHMemRegion memSrcGrid(mem_buffer_grid_src, CFG_MEMSIZE_BYTES_PerGrid);
    VHMemRegion memDstGrid(mem_buffer_grid_dst, CFG_MEMSIZE_BYTES_PerGrid);
    VHMemRegion memArrObjs(mem_buffer_objects, CFG_MEMSIZE_BYTES_Objects);
    VHMemRegion memArrSpns(mem_buffer_spans, CFG_MEMSIZE_BYTES_Spans);

#ifdef VHLIB_OPTIMAL_GRID_FLEX
    uint16_t gridw = 1 << VHLIB_OPTIMAL_GRID_LX;
    uint16_t gridh = 1 << VHLIB_OPTIMAL_GRID_LY;
#endif

#ifdef VHLIB_OPTIMAL_GRID_FIXED
    uint16_t gridw = 1 << VHLIB_OPTIMAL_GRID_LX;
    uint16_t gridh = 1 << VHLIB_OPTIMAL_GRID_LY;
#endif

    verr retsetup = detector.Setup(
        cfg,
        gridw,
        gridh,
        memSrcGrid,
        memDstGrid,
        memArrObjs,
        memArrSpns,
        this,
        CALLBACK_VHLIBOPTIMAL_Border,
        CALLBACK_VHLIBOPTIMAL_Content,
        CALLBACK_VHLIBOPTIMAL_Benchmark);

    if (vok == retsetup)
    {
        printf("VHLIBOptimal Initialized\n");
    }
    else
    {
        return verrmsg(103, "VHLIBOptimal::Setup() failed!");
    }

    // Show Memory layout
    detector.MemoryLayout().ShowMemoryStat();

    // Return initialization status
    return vok;
}

/**
 *
 */
void TestLibraryContainer::CallbackBorder(
    uint8_t cmd,
    uint8_t dirh,
    uint8_t dirv,
    uint16_t cellx,
    uint16_t celly)
{
}

/**
 *
 */
void TestLibraryContainer::CallbackContent(
    uint32_t cell1,
    uint32_t cell2,
    uint8_t dir)
{
}

/**
 *
 */
void TestLibraryContainer::CallbackBenchmark(int cmd, int param)
{

    switch (cmd)
    {

    case vhliboptimal::eCmdBenchmarkMemalloc:
        break;

    case vhliboptimal::eCmdBenchmarkSampling:
        if (!param)
            tsSampling.start();
        else
            tsSampling.stop();
        break;

    case vhliboptimal::eCmdBenchmarkScan:
        if (!param)
        {
            tsScanning.start();
        }
        else
        {
            tsScanning.stop();
        }
        break;

    case vhliboptimal::eCmdBenchmarkSubfuncFigure:
        break;

    default:
    {
    }
    }
}

/**
 *
 */
void TestLibraryContainer::CALLBACK_VHLIBOPTIMAL_Border(
    void *caller,
    uint8_t cmd,
    uint8_t dirh,
    uint8_t dirv,
    uint16_t cellx,
    uint16_t celly)
{
    if (caller == nullptr)
        return;

    auto *self = static_cast<TestLibraryContainer *>(caller);
    self->CallbackBorder(cmd, dirh, dirv, cellx, celly);
}

/**
 *
 */
void TestLibraryContainer::CALLBACK_VHLIBOPTIMAL_Content(
    void *caller,
    uint32_t cell1,
    uint32_t cell2,
    uint8_t dir)
{
    if (caller == nullptr)
        return;

    auto *self = static_cast<TestLibraryContainer *>(caller);
    self->CallbackContent(cell1, cell2, dir);
}

/**
 *
 */
void TestLibraryContainer::CALLBACK_VHLIBOPTIMAL_Benchmark(
    void *caller,
    int cmd,
    int param)
{
    if (caller == nullptr)
        return;

    auto *self = static_cast<TestLibraryContainer *>(caller);
    self->CallbackBenchmark(cmd, param);
}
