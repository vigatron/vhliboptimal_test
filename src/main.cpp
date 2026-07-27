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

#if VHLIB_OPTIMAL_VERSION_MAJOR !=0 || VHLIB_OPTIMAL_VERSION_MINOR != 7
#error "Depends on vhliboptimal library"
#endif


using namespace vhliboptimal;

static QImage imgsrc;
static QImage imgdst;
static QImage imgbw8;

stBenchmarkParams bench;

//
vhliboptimal::VHLibOptimal detector;

//
TimerStamp ts;

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
        IFACE_OPTIMAL_Content );

    if(flag1)
        return verrmsg(1, "Invalid settings");

    detector.SetSortMode(0);

    int imgsrc = 0;
    
    ts.start();
    verr flag2 = detector.Run(imgsrc);
    ts.stop();

    if(flag2)
        return verrmsg(2, "Shape contour detection failed");

    const CellsMatrix & cmtx = detector.GetCMatrix();

    bench.imageWidth    = cfg.imageWidth;
    bench.imageHeight   = cfg.imageHeight;
    bench.cellsw        = cmtx.CellsX();
    bench.cellsh        = cmtx.CellsY();
    bench.cellst        = cmtx.CellsT();
    bench.buffsize      = cmtx.BitMaskSizeBytes();
    bench.objscnt       = detector.GetObjectsCount();

    return vok;
}

/**
 * 
 */
void generateOutPic() {

    imgdst = QImage(imgsrc.width(), imgsrc.height(), imgsrc.format());
    imgdst.fill(Qt::black);

    {
        QPainter painter(&imgdst);
        painter.setPen(QColor(0, 200, 0));
        painter.setBrush(QColor(0, 96, 0));

        for(int i = 0; i < detector.GetObjectsCount(); i++) {
            const vhliboptimal::VHOptimalFigure & obj = detector.GetObject(i);
            const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();
            const strect rect = obj.PosAbs(cmtx);

            int w = rect.x2 - rect.x1 + 1;
            int h = rect.y2 - rect.y1 + 1;
            painter.drawRect(rect.x1, rect.y1, w, h);
        }

        painter.end();
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

    bench.filename      = fname;
    bench.cellsize      = cellsize;
    
    int passcnt       = 16;

    bench.tsavg         = 0;
    bench.tsmin         = 0;
    bench.tsmax         = 0;

    long arrResults[passcnt] = {0};

    for(int i=0; i < passcnt;i++) {

        // Exception ?
        if(iteration(cellsize)) break;

        arrResults[i] = ts.result_ms();
        std::cout << "Elapsed: " << arrResults[i] << " ms" << std::endl;

        if(!i) {
            bench.tsmin = arrResults[i];
            bench.tsmax = arrResults[i];
            bench.tsavg = arrResults[i];
        } else {
            if(arrResults[i] < bench.tsmin) bench.tsmin = arrResults[i];
            if(arrResults[i] > bench.tsmax) bench.tsmax = arrResults[i];
            bench.tsavg += arrResults[i];
        }
    }

    bench.tsavg /= passcnt;
    std::cout << "Average: " << bench.tsavg << " ms/frame" << std::endl;

    // 3. Save reslts
    SaveBenchmark(bench);
    generateOutPic();
    saveResults(fname);

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
