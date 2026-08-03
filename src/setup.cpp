#include "vhplatform.hpp"
#include "setup.hpp"
#include "vhliboptimal.hpp"
#include "iface.hpp"

extern vhliboptimal::VHLibOptimal detector;

static std::vector<uint8_t> memblock;

verr VHLIBOptimalSetup(uint8_t levelcs) {

    // 2. Memory allocation
    size_t membytes = detector.CalcMemory();
    asrts(membytes >    1 * F1K, 1, "VHLibOptimal::CalcMemory()");
    asrts(membytes <  512 * F1K, 1, "VHLibOptimal::CalcMemory()");

    // Allocate memory with std::vector<uint8_t>
    memblock.assign(membytes, 0);
    verr r = detector.SetupMemory(memblock.data(), memblock.size());
    if(r) return verrmsg(1, "VHLIBOptimalSetup() memory allocation issue");


    const vhliboptimal::stConfig cfg = {

        .spccnt         = 0,
        .levelcs        = levelcs,
        .minColorVal    = VHAPP_OPTIMAL_TEST_FLTVAL,

        // Min/Max object size filter
        .min_obj_width  = 2,
        .min_obj_height = 2,
        .max_obj_width  = F1K * 4,
        .max_obj_height = F1K * 4,

        .sortMode       = 0,
        .loglevel       = VHLIB_OPTIMAL_LOG_LEVEL
    };

    verr flag1 = detector.Setup(
        cfg,
        IFACE_OPTIMAL_Border,
        IFACE_OPTIMAL_Content,
        IFACE_OPTIMAL_Benchmark );

    if(flag1)
        return verrmsg(1, "Invalid settings");


    // Return initialization status
    return vok;
}