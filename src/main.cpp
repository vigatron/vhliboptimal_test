#include "vhplatform.hpp"
#include "version_vhplatform.h"

#include "vhliboptimal.hpp"
#include "vhliboptimallog.hpp"
#include "version_vhliboptimal.h"

#include "iface.hpp"
#include "vhtimerstamp.hpp"
#include "vhargs.hpp"
#include "benchmark.hpp"

#include <QImage>
#include <QPainter>
#include <QFileInfo>


#if VHLIB_PLATFORM_VERSION_HEX != 400
#error "Depends on vhlibplatform library"
#endif

#if VHLIB_OPTIMAL_VERSION_MAJOR !=0 || VHLIB_OPTIMAL_VERSION_MINOR != 8
#error "Depends on vhliboptimal library"
#endif


using namespace vhliboptimal;

static QImage imgsrc;
static QImage imgdst;
static QImage imgbw8;

// Benchmark related pass
TSArray     arrtsSampling;
TSArray     arrtsScanning;

extern TimerStamp  tsSampling;      // IFACE Callbacks
extern TimerStamp  tsScanning;      // IFACE Callbacks

// Benchmark related summary
stBenchmarkParams benchResults;


//
vhliboptimal::VHLibOptimal detector;

/**
 * 
 */
const QImage & GetOptimalBWQImage() {
    return imgbw8;
};


verr iteration(uint8_t cellsize) {

    const vhliboptimal::stConfig cfg = {
        .imageWidth     = (uint16_t)imgsrc.width(),
        .imageHeight    = (uint16_t)imgsrc.height(),
        .spccnt         = 0,
        .cellsize       = cellsize,
        .minColorVal    = 200,
        .min_obj_width  = 2,
        .min_obj_height = 2,
        .max_obj_width  = F1K * 4,
        .max_obj_height = F1K * 4,
        .loglevel       = vhliboptimal::LOG_LEVEL_BASE
    };

    verr flag1 = detector.Setup(
        cfg,
        IFACE_OPTIMAL_GetLinePixels,
        IFACE_OPTIMAL_Border,
        IFACE_OPTIMAL_Content,
        IFACE_OPTIMAL_Benchmark
     );

    if(flag1)
        return verrmsg(1, "Invalid settings");

    detector.SetSortMode(0);

    int imgsrc = 0;
    
    verr flag2 = detector.Run(imgsrc);

    if(flag2)
        return verrmsg(2, "Shape contour detection failed");

    const CellsMatrix & cmtx = detector.GetCMatrix();

    benchResults.imageWidth    = cfg.imageWidth;
    benchResults.imageHeight   = cfg.imageHeight;
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
void generateOutPic() {

    imgdst = QImage(imgsrc.width(), imgsrc.height(), imgsrc.format());
    imgdst.fill(Qt::black);

    int pwdth = (imgsrc.width() / 1000) + 1;

    {

        for(int fign = 0; fign < detector.GetObjectsCount(); fign++) {

            const vhliboptimal::VHOptimalFigure & obj = detector.GetObject(fign);
            const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();
            const strect rect = obj.PosAbs(cmtx);

            // Fill cells
            {
                QPainter painter(&imgdst);

                painter.setPen(QColor(0, 0, 192));
                painter.setBrush(QColor(0, 0, 100));

                for(int spann=0; spann < obj.SpansCount(); spann++) {
                    const vhliboptimal::stspan & span = obj.Span(spann);

                    for(int celln=span.n;celln < (span.n + span.l); celln++) {
                        auto [cx, cy] = cmtx.CellXY(celln);
                        int cs = cmtx.CellSize();
                        painter.drawRect(cx * cs, cy * cs, cs, cs);
                    }
                }

                painter.end();
            }

            // max size
            {
                QPainter painter(&imgdst);

                painter.setPen( QPen(QColor(0, 255, 0), pwdth));
                painter.setBrush(Qt::NoBrush);

                int w = rect.x2 - rect.x1 + 1;
                int h = rect.y2 - rect.y1 + 1;
                painter.drawRect(rect.x1, rect.y1, w, h);

                painter.end();
            }

        }

    }

    {
        for(int y = 0; y < imgsrc.height(); y++) {
            for(int x = 0; x < imgsrc.width(); x++) {
                QRgb pxl = imgbw8.pixel(x, y);
                if(qBlue(pxl)>200)
                    imgdst.setPixel(x, y, pxl);
            }
        }
    }
    

}

/**
 * 
 */
void saveResults(const std::string & srcfname) {

    QFileInfo info(QString::fromStdString(srcfname));

    QString file1 = info.baseName() + "_src.jpg";
    QString file2 = info.baseName() + "_bw8.jpg";
    QString file3 = info.baseName() + "_out.jpg";

    imgsrc.save(file1, "jpg", 50);
    imgbw8.save(file2, "jpg", 50);
    imgdst.save(file3, "jpg", 50);

}

/**
 * 
 */
verr runtest(const std::string & fname, int cellsize) {

    // 1. Read source image and convert to Grayscale
    VHLibOptimalLogger::lineout("File Name: " + fname);

    bool flagl = imgsrc.load(QString::fromStdString(fname));
    if(!flagl) {
        return verrmsg(1, "Invalid image file:" + fname);
    }

    imgbw8 = imgsrc.convertToFormat(QImage::Format_Grayscale8);


    // 2. Run benchmark tests

    benchResults.filename      = fname;
    benchResults.cellsize      = cellsize;


    for(int i=0; i < VHLIBOPTIMAL_TEST_PASS_COUNT;i++) {

        // Exception ?
        if(iteration(cellsize)) break;

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
    generateOutPic();
    
    #if SAVE_RESULTS > 0
    saveResults(fname);
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
        return runtest(paramFileName, paramCellSize);
    }

    return 1;
}
