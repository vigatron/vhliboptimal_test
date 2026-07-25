#include "vhplatform.hpp"
#include "version_vhplatform.h"

#include "vhliboptimal.hpp"
#include "vhliboptimallog.hpp"
#include "version_vhliboptimal.h"

#include "iface.hpp"
#include "vhtimerstamp.hpp"

#include <QImage>
#include <QFileInfo>


#if VHLIB_PLATFORM_VERSION_HEX != 400
#error "Depends on vhlibplatform library"
#endif


#if VHLIB_OPTIMAL_VERSION_HEX != 702
#error "Depends on vhliboptimal library"
#endif


using namespace vhliboptimal;

static QImage imgsrc;
static QImage imgdst;
static QImage imgbw8;

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

/**
 * 
 */
std::string vharg(int argn, int argc, char *argv[]) {
    std::string r;

    if(argn + 2 <= argc) {
        r = std::string(argv[argn+1]);
    }

    return r;
}

verr iteration() {

    const vhliboptimal::stConfig cfg = {
        .imageWidth     = (uint16_t)imgsrc.width(),
        .imageHeight    = (uint16_t)imgsrc.height(),
        .spccnt         = 0,
        .cellsize       = 2,
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

    int imgsrc = 0;
    
    ts.start();
    verr flag2 = detector.Run(imgsrc);
    ts.stop();

    if(flag2)
        return verrmsg(2, "Shape contour detection failed");

    return vok;
}

/**
 * 
 */
void generateOutPic() {

    imgdst = QImage(imgsrc.width(), imgsrc.height(), imgsrc.format());
    imgdst.fill(Qt::black);

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
verr runtest(const std::string & fname) {

    VHLibOptimalLogger::lineout("File Name: " + fname);

    bool flagl = imgsrc.load(QString::fromStdString(fname));
    if(!flagl) {
        return verrmsg(1, "Invalid image file:" + fname);
    }

    imgbw8 = imgsrc.convertToFormat(QImage::Format_Grayscale8);

    long long tssumm = 0;
    int tscnt  = 16;
    for(int i=0;i < tscnt;i++) {
        if(iteration()) { tssumm = 0; break; }
        tssumm += ts.result_ms();
        std::cout << "Elapsed: " << ts.result_ms() << " ms" << std::endl;
    }

    std::cout << "Average: " << tssumm / tscnt << " ms/frame" << std::endl;

    generateOutPic();
    saveResults(fname);

    return vok;
}

/**
 * 
 */
int main(int argc, char *argv[]) {

    std::string fname = vharg(0, argc, argv);

    if(!fname.empty()) {
        return runtest(fname);
    }

    return 1;
}

// for(int i = 0; i < detector.GetObjectsCount(); i++) {
//     const vhliboptimal::VHOptimalFigure & obj = detector.GetObject(i);
//     const vhliboptimal::CellsMatrix & cmtx = detector.GetCMatrix();
//     obj.Border(cmtx, IFACE_OPTIMAL_SetPos);
// }
