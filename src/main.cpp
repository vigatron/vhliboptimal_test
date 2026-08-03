#include "main.hpp"

#include "vhtimerstamp.hpp"
#include "vhargs.hpp"
#include "benchmark.hpp"

#include "imgsrc/imgsrc.hpp"
#include "imgdst/imgdst.hpp"

#include "setup.hpp"


vhliboptimal::VHLibOptimal      detector;

VHImageSource                   imgSource;
VHImageDestination              imgDest;


// Benchmark related
TSArray     arrtsSampling;

TSArray     arrtsScanning;

// Measured when called with callback / IFACE Callbacks
TimerStamp  tsSampling;

// Measured when called with callback / IFACE Callbacks
TimerStamp  tsScanning;

// Benchmark related .md report / summary
stBenchmarkParams benchResults;


void fillMarkdownSrcImg(
    const std::string & fname,
    uint8_t levelcs
) {

    const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();

    // Размер картинки в пикселях, длинна
    benchResults.imageWidth    = imgSource.GetBWImage().width();

    // Размер картинки в пикселях, высота
    benchResults.imageHeight   = imgSource.GetBWImage().height();

    benchResults.cellsw        = cmtx.CellsX();
    benchResults.cellsh        = cmtx.CellsY();
    benchResults.cellst        = cmtx.CellsT();

    benchResults.buffsize      = cmtx.BitMaskSizeBytes();
    benchResults.objscnt       = detector.ObjectsCount();

    benchResults.filename      = fname;
    benchResults.cellsize      = 1 << levelcs;

    // Benchmark results
    benchResults.ts_smp_min         = arrtsSampling.resultmin();
    benchResults.ts_smp_avg         = arrtsSampling.result();
    benchResults.ts_smp_max         = arrtsSampling.resultmax();

    benchResults.ts_scn_min         = arrtsScanning.resultmin();
    benchResults.ts_scn_avg         = arrtsScanning.result();
    benchResults.ts_scn_max         = arrtsScanning.resultmax();

    benchResults.ts_fin_min         = benchResults.ts_smp_min + benchResults.ts_scn_min;
    benchResults.ts_fin_avg         = benchResults.ts_smp_avg + benchResults.ts_scn_avg;
    benchResults.ts_fin_max         = benchResults.ts_smp_max + benchResults.ts_scn_max;

}

/**
 * 
 */
verr iteration(uint8_t levelcs) {


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

    // Memory allocation & Grid settings
    if(VHLIBOptimalSetup(levelcs))
        return verrmsg(2, "VHLIBOptimalSetup() failed");

    for(int i=0; i < VHAPP_OPTIMAL_TEST_PASS_COUNT;i++) {

        // Exception ?
        if(iteration(levelcs)) break;

        int t1 = tsSampling.result_ms();
        arrtsSampling.add(t1);

        int t2 = tsScanning.result_ms();
        arrtsScanning.add(t2);

        std::cout
            << "> Sampling: " << t1 << "ms"
            <<", Scanning: " << t2 << "ms"
            << std::endl << std::endl;
    }

    fillMarkdownSrcImg(fname, levelcs);

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

    // First parameter: FileName
    std::string paramFileName = vhargstr(0, argc, argv);
    if(paramFileName.empty())
        return 1;

    #ifdef VHAPP_OPTIMAL_TEST_CONVERT_BMP
    int test_convert_bmp(const QString & fname);
    return test_convert_bmp(QString::fromStdString(paramFileName));
    #endif

    // Second param GridSize
    int paramCellSize = vhargint(1, argc, argv);
    if(paramCellSize == -1) { paramCellSize = 2; }

    return runtest(paramFileName, __builtin_ctz(paramCellSize));
}
