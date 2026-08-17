#pragma once

// #include "vhplatform.hpp"
#include "platform/platform.hpp"

#include "vhliboptimal.hpp"

#include "timer/vhtimerstamp.hpp"
#include "timer/timeaverager.hpp"

// #include "report/report.hpp"

#include "log/log.hpp"


class TestLibraryContainer {

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
        vhliboptimal::VHLibOptimal          detector;

        // Benchmark: sampling related
        TimerAverager                       arrtsSampling;

        // Benchmark: scan related
        TimerAverager                       arrtsScanning;

        // Measured when called with callback / IFACE Callbacks
        VHTimerStamp                        tsSampling;

        // Measured when called with callback / IFACE Callbacks
        VHTimerStamp                        tsScanning;

        /**
         * 
         */
        verr    CopyAndScale            (uint16_t imageid, uint8_t sclevel);

        /**
         * 
         */
        verr    TestImageAverage        (uint16_t imageid, uint8_t levelcs);

        /**
         * 
         */
        verr    TestImageIteration      (uint16_t imageid, uint8_t levelcs);

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



    // #ifdef VHAPP_OPTIMAL_TEST_CONVERT_BMP
    // int test_convert_bmp(const QString & fname);
    // return test_convert_bmp(QString::fromStdString(paramFileName));
    // #endif

    // // Prepare Frame:
    // //  Convert Original Image to BitField
    // //  (Downsampling or Bit-to-bit transfer)
    // int startx = 0, starty = 0;
    // 
    // uint16_t cellsx = cmtx.CellsX();
    // uint16_t cellsy = cmtx.CellsY();

    // if( imgSource.convert(
    //         startx, starty, cellsx, cellsy, levelcs,
    //         detector.GetCMatrix(), detector.BitFieldSrc(), detector.FilterLevel()) ) {
    //             return verrmsg(3, "Source image conversion issues"); }

    // #if SAVE_RESULTS > 0
    // // 4. Generate and save images
    // {
    //     QFileInfo info(QString::fromStdString(fname));

    //     QString fnameOrigImage = info.baseName() + "_src.jpg";
    //     imgSource.saveOrigImage(fnameOrigImage.toStdString());

    //     QString fnameBWImage = info.baseName() + "_bw8.jpg";
    //     imgSource.saveBWImage(fnameBWImage.toStdString());
    // }

    // {
    //     QFileInfo info(QString::fromStdString(fname));
    //     QString fnameout = info.baseName() + "_out.jpg";
    //     imgDest.generateOutPic(imgSource.GetImage(), detector, fnameout);
    // }
    // #endif


    // const std::string & fname, int levelcs





#ifdef VH_COMMENT_PLATFORM_PC

#include "imgsrc/imgsrc.hpp"
#include "imgdst/imgdst.hpp"


struct stContainerConfig {
    std::string fname;
    uint8_t *bmparr;
    uint32_t bmpsize;
    uint16_t offssx;
    uint16_t offssy;
    uint16_t width;
    uint16_t height;
    uint8_t  levelcs;
};

// Parse Command line file
TestLibraryContainer::stContainerConfig cfg = {
    .bmparr     = memblock_data(),
    .bmpsize    = memblock_size(),
    .offssx     = 0,
    .offssy     = 0,
    .width      = 0,
    .height     = 0,
    .levelcs    = (uint8_t) __builtin_ctz(paramCellSize)
};


VHImageSource                   imgSource;

VHImageDestination              imgDest;

//
std::vector<uint8_t>            memBlockAligned;

/**
 *
 */
void GenerateReport(const stContainerConfig & cfg) {
    const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();
    gobjReport.SetFileName(cfg.fname);

    // gobjReport.SetImgProps(imgSource.GetBWImage().width(), imgSource.GetBWImage().height() );
    gobjReport.SetImgProps(0, 0);

    gobjReport.SetMisc(cmtx, cfg.levelcs, detector.ObjectsCount());
    gobjReport.SetTimings(arrtsSampling, arrtsScanning);
    gobjReport.SaveResults();
}

#endif
