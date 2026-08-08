#pragma once

#include "vhplatform.hpp"
#include "vhliboptimal.hpp"

#include "imgsrc/imgsrc.hpp"
#include "imgdst/imgdst.hpp"

#include "timer/vhtimerstamp.hpp"
#include "timer/timeaverager.hpp"
#include "report/report.hpp"

#include "iface.hpp"

#include "log/log.hpp"

// Reference to embedded picture
uint8_t *   embedded_bmp_data();
uint32_t    embedded_bmp_size();


class TestLibraryContainer {

    public:

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

        /**
         * 
         */
        // const std::string & fname, int levelcs
        verr StartTest(const stContainerConfig & cfg) {

            // Memory allocation & Grid settings
            // TODO: Check alignment if need 
            if(VHLIBOptimalSetup(cfg.levelcs))
                return verrmsg(2, "VHLIBOptimalSetup() failed");

            // Multiple cycles for average measurements values
            for(int i=0; i < VHLIBOPTIMAL_TEST_PASS_COUNT;i++) {

                detector.BitFieldSrc().ClearArea(detector.GetCMatrix());

                // Transfer source image bitfield
                for(uint32_t i = 0; i < cfg.bmpsize; i++) {
                    verr r = detector.BMPParserByte(cfg.bmparr[i], cfg.levelcs);
                    if(r) return r;
                }

                detector.BitFieldSrc().ClearBorder(detector.GetCMatrix());

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

            GenerateReport(cfg);

            std::cout << "Done" << std::endl;

            return vok;
        }

        /**
         * 
         */
        void connectCallbackBenchmark(void *userData, int cmd, int param) {

            switch(cmd) {

                case vhliboptimal::eCmdBenchmarkMemalloc:
                    break;

                case vhliboptimal::eCmdBenchmarkSampling:
                    if(!param) tsSampling.start(); else tsSampling.stop();
                    break;

                case vhliboptimal::eCmdBenchmarkScan:
                    if(!param)
                        tsScanning.start();
                    else
                        tsScanning.stop();

                    break;

                case vhliboptimal::eCmdBenchmarkSubfuncFigure:
                    break;

                default: { }
            }

        }

        /**
         * 
         */
        verr VHLIBOptimalSetup(uint8_t levelcs) {

            // 2. Memory allocation
            size_t membytes = detector.CalcMemory();
            asrts(membytes >    1 * F1K, 1, "VHLibOptimal::CalcMemory()");
            asrts(membytes <  512 * F1K, 1, "VHLibOptimal::CalcMemory()");

            // Allocate memory with std::vector<uint8_t>
            memBlockAligned.assign(membytes, 0);
            verr r = detector.SetupMemory(memBlockAligned.data(), memBlockAligned.size());
            if(r) return verrmsg(1, "VHLIBOptimalSetup() memory allocation issue");

            //
            const vhliboptimal::stConfig cfg = {

                .spccnt         = 0,
                .levelcs        = levelcs,
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

    private:

        // Global variables
        vhliboptimal::VHLibOptimal      detector;

        //
        VHImageSource                   imgSource;

        //
        VHImageDestination              imgDest;

        // Benchmark: sampling related
        TimerAverager                   arrtsSampling;

        // Benchmark: scan related
        TimerAverager                   arrtsScanning;

        // Measured when called with callback / IFACE Callbacks
        TimerStamp                      tsSampling;

        // Measured when called with callback / IFACE Callbacks
        TimerStamp                      tsScanning;

        //
        std::vector<uint8_t>            memBlockAligned;


        /**
         *
         */
        void GenerateReport(const stContainerConfig & cfg) {
            const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();
            gobjReport.SetFileName(cfg.fname);
            gobjReport.SetImgProps(imgSource.GetBWImage().width(), imgSource.GetBWImage().height() );
            gobjReport.SetMisc(cmtx, cfg.levelcs, detector.ObjectsCount());
            gobjReport.SetTimings(arrtsSampling, arrtsScanning);
            gobjReport.SaveResults();
        }

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
