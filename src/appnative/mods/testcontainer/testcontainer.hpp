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

// #include "timer/vhtimerstamp.hpp"
// #include "benchmark.hpp"
// #include <QImage>


class TestLibraryContainer {

    public:

        verr TestSingleFile(const std::string & filename) {

            return verror(1);
        }

        verr TestInternalExamples() {

            return verror(1);
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

        verr VHLIBOptimalSetup(uint8_t levelcs) {

            // 2. Memory allocation
            size_t membytes = detector.CalcMemory();
            asrts(membytes >    1 * F1K, 1, "VHLibOptimal::CalcMemory()");
            asrts(membytes <  512 * F1K, 1, "VHLibOptimal::CalcMemory()");

            // Allocate memory with std::vector<uint8_t>
            memblock.assign(membytes, 0);
            verr r = detector.SetupMemory(memblock.data(), memblock.size());
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
        std::vector<uint8_t>            memblock;


};
