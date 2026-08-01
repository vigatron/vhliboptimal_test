#include "main.hpp"

#include "iface.hpp"
#include "vhtimerstamp.hpp"
#include "vhargs.hpp"
#include "benchmark.hpp"

#include "imgsrc/imgsrc.hpp"
#include "imgdst/imgdst.hpp"



VHImageSource                   imgSource;
VHImageDestination              imgDest;

vhliboptimal::VHLibOptimal      detector;

// Benchmark related pass
TSArray     arrtsSampling;
TSArray     arrtsScanning;

extern TimerStamp  tsSampling;      // IFACE Callbacks
extern TimerStamp  tsScanning;      // IFACE Callbacks

// Benchmark related summary
stBenchmarkParams benchResults;



/**
 * 
 */
verr iteration(uint8_t levelcs) {


    const vhliboptimal::stConfig cfg = {

        .spccnt         = 0,
        .levelcs        = levelcs,
        .minColorVal    = 200,

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

    // Convert Original Image to BitField
    // Prepare Frame : Downsampling
    if(
        imgSource.convert(

            0, 0,
            detector.GetCMatrix().CellsX(),
            detector.GetCMatrix().CellsY(),
            levelcs,

            detector.GetCMatrix(),
            detector.BitFieldSrc(),
            detector.FilterLevel() )
        ) {
            return verrmsg(3, "Source image conversion issues");
        }

    verr flag2 = detector.Run();

    if(flag2)
        return verrmsg(2, "Shape contour detection failed");

    const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();

    benchResults.imageWidth    = imgSource.GetBWImage().width();
    benchResults.imageHeight   = imgSource.GetBWImage().height();
    benchResults.cellsw        = cmtx.CellsX();
    benchResults.cellsh        = cmtx.CellsY();
    benchResults.cellst        = cmtx.CellsT();
    benchResults.buffsize      = cmtx.BitMaskSizeBytes();
    benchResults.objscnt       = detector.GetObjectsCount();

    return vok;
}


/**
 * 
 */
verr runtest(const std::string & fname, int levelcs) {

    {
        std::string msg = "File Name: " + fname;
        vhliboptimal::log::lineout(msg.c_str());
    }

    // 1. Read source image and convert to Grayscale
    if(imgSource.load(fname)) {
        return verrmsg(1, "Invalid image file:" + fname);
    }

    // 2. Memory allocation
    size_t membytes = detector.CalcMemory();
    asrts(membytes >    1 * F1K, 1, "VHLibOptimal::CalcMemory()");
    asrts(membytes <  512 * F1K, 1, "VHLibOptimal::CalcMemory()");
    std::vector<uint8_t> memblock(membytes, 0);
    if(detector.SetupMemory(memblock.data(), memblock.size())) {
        return verrmsg(2, "VHLibOptimal::SetupMemory()");
    }

    // 3. Run benchmark tests

    benchResults.filename      = fname;
    benchResults.cellsize      = 1 << levelcs;

    for(int i=0; i < VHLIBOPTIMAL_TEST_PASS_COUNT;i++) {

        // Exception ?
        if(iteration(levelcs)) break;

        int t1 = tsSampling.result_ms();
        arrtsSampling.add(t1);

        int t2 = tsScanning.result_ms();
        arrtsScanning.add(t2);

        std::cout << "> Sampling: " << t1 << "ms, Scanning: " << t2 << "ms" << std::endl << std::endl;
    }


    benchResults.ts_smp_min         = arrtsSampling.resultmin();
    benchResults.ts_smp_avg         = arrtsSampling.result();
    benchResults.ts_smp_max         = arrtsSampling.resultmax();

    benchResults.ts_scn_min         = arrtsScanning.resultmin();
    benchResults.ts_scn_avg         = arrtsScanning.result();
    benchResults.ts_scn_max         = arrtsScanning.resultmax();

    benchResults.ts_fin_min         = benchResults.ts_smp_min + benchResults.ts_scn_min;
    benchResults.ts_fin_avg         = benchResults.ts_smp_avg + benchResults.ts_scn_avg;
    benchResults.ts_fin_max         = benchResults.ts_smp_max + benchResults.ts_scn_max;

    std::cout << "Min (ms): " << benchResults.ts_fin_min << " ms/frame" << std::endl;
    std::cout << "Avg (ms): " << benchResults.ts_fin_avg << " ms/frame" << std::endl;
    std::cout << "Max (ms): " << benchResults.ts_fin_max << " ms/frame" << std::endl;

    // 3. Save results
    SaveBenchmark(benchResults);
    
    // 4. Generate and save images
    
    #if SAVE_RESULTS > 0
    imgSource.saveResults(fname);

    {
        QFileInfo info(QString::fromStdString(fname));
        QString fnameout = info.baseName() + "_out.jpg";
        imgDest.generateOutPic(imgSource.GetImage(), detector, fnameout);
    }
    #endif

    std::cout << "Done" << std::endl;

    return vok;
}

/**
 * 
 */
int main(int argc, char *argv[]) {

    std::string     paramFileName   = vhargstr(0, argc, argv);
    int             paramCellSize   = vhargint(1, argc, argv);

    if(paramCellSize == -1) { paramCellSize = 2; }

    if(!paramFileName.empty()) {
        return runtest(paramFileName, __builtin_ctz(paramCellSize));
    }

    return 1;
}
