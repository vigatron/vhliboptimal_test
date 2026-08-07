#include "main.hpp"

#include "vhtimerstamp.hpp"
#include "vhargs.hpp"
#include "benchmark.hpp"

#include "imgsrc/imgsrc.hpp"
#include "imgdst/imgdst.hpp"

#include "setup.hpp"

#include "testcontainer.hpp"

#include "timer/timeaverager.hpp"

#include "report.hpp"


// * TestLibraryContainer *
// Test single file (passed as parameter)
// Test linked 512x512 B&W examples 1-7
TestLibraryContainer            testContainer;

// Global variables
vhliboptimal::VHLibOptimal      detector;

//
VHImageSource                   imgSource;

//
VHImageDestination              imgDest;

// Benchmark: sampling related
TimerAverager     arrtsSampling;

// Benchmark: scan related
TimerAverager     arrtsScanning;

// Measured when called with callback / IFACE Callbacks
TimerStamp  tsSampling;

// Measured when called with callback / IFACE Callbacks
TimerStamp  tsScanning;


/**
 * 
 */
verr runtest(const std::string & fname, int levelcs) {

    // filename to console
    vhliboptimal::log::partout("File Name: ");
    vhliboptimal::log::lineout(fname.c_str());

    // 1. Read source image and convert to Grayscale
    if(imgSource.load(fname)) {
        return verrmsg(1, "Invalid image file:" + fname);
    }

    // Memory allocation & Grid settings
    if(VHLIBOptimalSetup(levelcs))
        return verrmsg(2, "VHLIBOptimalSetup() failed");

    // Prepare Frame:
    //  Convert Original Image to BitField
    //  (Downsampling or Bit-to-bit transfer)
    int startx = 0, starty = 0;
    const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();
    uint16_t cellsx = cmtx.CellsX();
    uint16_t cellsy = cmtx.CellsY();

    if( imgSource.convert(
            startx, starty,
            cellsx, cellsy, levelcs,
            detector.GetCMatrix(),
            detector.BitFieldSrc(),
            detector.FilterLevel()) ) {
                return verrmsg(3, "Source image conversion issues"); }

    // Multiple cycles for average measurements values
    for(int i=0; i < VHAPP_OPTIMAL_TEST_PASS_COUNT;i++) {

        // Exception ?
        verr flagDetectionResults = detector.Run();
        if(flagDetectionResults) {
            verrmsg(2, "Shape contour detection failed");
            break;
        }

        int t_samp_us = tsSampling.result_us();
        arrtsSampling.add(t_samp_us);
        std::cout << "> " << "Sampling: " << t_samp_us << "uSec" << std::endl;

        int t_scan_us = tsScanning.result_us();
        arrtsScanning.add(t_scan_us);
        std::cout << "> " << "Scanning: " << t_scan_us << "uSec" << std::endl;
    }

    // Generate table
    gobjReport.SetFileName(fname);
    gobjReport.SetImgProps(imgSource.GetBWImage().width(), imgSource.GetBWImage().height() );
    gobjReport.SetMisc(cmtx, levelcs, detector.ObjectsCount());
    gobjReport.SetTimings(arrtsSampling, arrtsScanning);
    gobjReport.SaveResults();

    #if SAVE_RESULTS > 0
    // 4. Generate and save images
    {
        QFileInfo info(QString::fromStdString(fname));

        QString fnameOrigImage = info.baseName() + "_src.jpg";
        imgSource.saveOrigImage(fnameOrigImage.toStdString());

        QString fnameBWImage = info.baseName() + "_bw8.jpg";
        imgSource.saveBWImage(fnameBWImage.toStdString());
    }

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

    // A) Command line file       : Autosize to grid
    // B) Embedded .bmp example   : Autosize to grid

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
